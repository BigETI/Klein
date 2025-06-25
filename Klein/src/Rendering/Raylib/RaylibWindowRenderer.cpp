#include <chrono>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>

#include <raylib.h>

#include <Klein/Math/Rectangle.hpp>
#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/Color.hpp>
#include <Klein/Rendering/Raylib/RaylibWindowRenderer.hpp>
#include <Klein/Rendering/RenderingContext.hpp>

using namespace std;
using namespace std::chrono;

using namespace Klein::Math;
using namespace Klein::Rendering::Raylib;

RaylibWindowRenderer::RaylibWindowRenderer(const string& title, size_t width, size_t height) : title(title), width(width), height(height) {
	if (IsWindowReady()) {
		throw runtime_error("raylib window has been already initialized.");
	}
	InitWindow(static_cast<int>(width), static_cast<int>(height), title.c_str());
	SetExitKey(KEY_NULL);
	raylibTexture2DResourceManager.Initialize();
}

RaylibWindowRenderer::~RaylibWindowRenderer() {
	raylibTexture2DResourceManager.Deinitialize();
	CloseWindow();
}

const string& RaylibWindowRenderer::GetTitle() const noexcept {
	return title;
}

string& RaylibWindowRenderer::GetTitle(string& result) const {
	return result = title;
}

const size_t RaylibWindowRenderer::GetWidth() const noexcept {
	return width;
}

const size_t RaylibWindowRenderer::GetHeight() const noexcept {
	return height;
}

void RaylibWindowRenderer::Render(const vector<RenderingContext>& renderingContexts, const high_resolution_clock::duration& deltaTime) {
	if (IsWindowReady()) {
		BeginDrawing();
		for (const auto& rendering_context : renderingContexts) {
			Klein::Math::Vector2<float> camera_position(rendering_context.GetCameraPosition());
			camera.target = {
				camera_position.x,
				-camera_position.y
			};
			::Vector2 window_scale_dpi(GetWindowScaleDPI());
			camera.offset = {
				GetRenderWidth() * rendering_context.GetCameraAlignment().x / window_scale_dpi.x,
				GetRenderHeight() * rendering_context.GetCameraAlignment().y / window_scale_dpi.y
			};
			camera.rotation = rendering_context.GetCameraRotation();
			camera.zoom = rendering_context.GetCameraZoom();
			if (rendering_context.IsClearingBackground()) {
				const Color<float>& clear_background_color(rendering_context.GetClearBackgroundColor());
				ClearBackground(
					{
						static_cast<unsigned char>(clamp(clear_background_color.red * 255.0f, 0.0f, 255.0f)),
						static_cast<unsigned char>(clamp(clear_background_color.green * 255.0f, 0.0f, 255.0f)),
						static_cast<unsigned char>(clamp(clear_background_color.blue * 255.0f, 0.0f, 255.0f)),
						static_cast<unsigned char>(clamp(clear_background_color.alpha * 255.0f, 0.0f, 255.0f))
					}
				);
			}
			BeginMode2D(camera);
			for (const auto& rendering_context_element : rendering_context) {
				shared_ptr<Texture2D> texture_2d;
				const Klein::Math::Rectangle<float>& rectangle(rendering_context_element->GetRectangle());
				const Klein::Math::Vector2<float>& origin(rendering_context_element->GetPivot() * rectangle.size);
				const Klein::Rendering::Color<float>& color(rendering_context_element->GetColor());
				::Color converted_color(
					{
						static_cast<unsigned char>(clamp(color.red * 255.0f, 0.0f, 255.0f)),
						static_cast<unsigned char>(clamp(color.green * 255.0f, 0.0f, 255.0f)),
						static_cast<unsigned char>(clamp(color.blue * 255.0f, 0.0f, 255.0f)),
						static_cast<unsigned char>(clamp(color.alpha * 255.0f, 0.0f, 255.0f))
					}
				);
				if (rendering_context_element->IsTexture2DVisible() && raylibTexture2DResourceManager.TryGettingResource(rendering_context_element->GetTexture2DResourceID(), texture_2d)) {
					const Klein::Math::Rectangle<float>& texture_2D_source_rectangle(rendering_context_element->GetTexture2DSourceRectangle());
					DrawTexturePro(
						*texture_2d,
						{
							texture_2D_source_rectangle.position.x * static_cast<float>(texture_2d->width),
							texture_2D_source_rectangle.position.y * static_cast<float>(texture_2d->height),
							texture_2D_source_rectangle.size.x * static_cast<float>(texture_2d->width),
							texture_2D_source_rectangle.size.y * static_cast<float>(texture_2d->height)
						},
					{
						rectangle.position.x,
						-rectangle.position.y,
						rectangle.size.x,
						rectangle.size.y
					},
					{
						origin.x,
						origin.y
					},
						-rendering_context_element->GetRotation(),
						converted_color
					);
				}
				shared_ptr<Font> font;
				if (rendering_context_element->IsTextVisible() && !rendering_context_element->GetText().empty() && raylibFontResourceManager.TryGettingResource(rendering_context_element->GetFontResourceID(), font)) {
					DrawTextPro(
						*font,
						rendering_context_element->GetText().c_str(),
						{
							rectangle.position.x,
							-rectangle.position.y,
						},
					{
						origin.x,
						origin.y
					},
						-rendering_context_element->GetRotation(),
						rendering_context_element->GetTextFontSize(),
						rendering_context_element->GetTextSpacing(),
						converted_color
					);
				}
			}
			EndMode2D();
		}
		EndDrawing();
	}

	// TODO: Cleanup resource manager of unused resources
}
