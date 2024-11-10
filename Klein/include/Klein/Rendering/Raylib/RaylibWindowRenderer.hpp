#pragma once

#include <chrono>
#include <string>

#include <raylib.h>

#include "../../Exportables/Exportable.hxx"
#include "../../ResourceManagement/Raylib/RaylibTexture2DResourceManager.hpp"
#include "../IRenderer.hpp"
#include "../RenderingContext.hpp"

namespace Klein::Rendering::Raylib {
	class RaylibWindowRenderer : public Klein::Rendering::IRenderer {
	public:

		KLEIN_API RaylibWindowRenderer(const std::string& title, unsigned int width, unsigned int height);

		RaylibWindowRenderer(const RaylibWindowRenderer&) = delete;
		RaylibWindowRenderer(RaylibWindowRenderer&&) = delete;

		KLEIN_API ~RaylibWindowRenderer();

		KLEIN_API const std::string& GetTitle() const noexcept;
		KLEIN_API std::string& GetTitle(std::string& result) const;
		KLEIN_API const unsigned int GetWidth() const noexcept;
		KLEIN_API const unsigned int GetHeight() const noexcept;
		KLEIN_API void Render(const RenderingContext& renderingContext, std::chrono::high_resolution_clock::duration deltaTime) override;

		RaylibWindowRenderer& operator =(const RaylibWindowRenderer&) = delete;
		RaylibWindowRenderer& operator =(RaylibWindowRenderer&&) = delete;

	private:

		const std::string& title;
		unsigned int width;
		unsigned int height;
		Camera2D camera;
		Klein::ResourceManagement::Raylib::RaylibTexture2DResourceManager raylibTexture2DResourceManager;
	};
}
