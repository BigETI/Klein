#pragma once

#include <chrono>
#include <string>

#include <raylib.h>

#include "../../Exportables/Exportable.hxx"
#include "../../ResourceManagement/Raylib/RaylibTexture2DResourceManager.hpp"
#include "../IRenderer.hpp"
#include "../RenderingContext.hpp"

namespace NGE::Rendering::Raylib {
	class RaylibWindowRenderer : public NGE::Rendering::IRenderer {
	public:

		NGE_API RaylibWindowRenderer(const std::string& title, unsigned int width, unsigned int height);

		RaylibWindowRenderer(const RaylibWindowRenderer&) = delete;
		RaylibWindowRenderer(RaylibWindowRenderer&&) = delete;

		NGE_API ~RaylibWindowRenderer();

		NGE_API const std::string& GetTitle() const noexcept;
		NGE_API std::string& GetTitle(std::string& result) const;
		NGE_API const unsigned int GetWidth() const noexcept;
		NGE_API const unsigned int GetHeight() const noexcept;
		NGE_API void Render(const RenderingContext& renderingContext, std::chrono::high_resolution_clock::duration deltaTime) override;

		RaylibWindowRenderer& operator =(const RaylibWindowRenderer&) = delete;
		RaylibWindowRenderer& operator =(RaylibWindowRenderer&&) = delete;

	private:

		const std::string& title;
		unsigned int width;
		unsigned int height;
		Camera2D camera;
		NGE::ResourceManagement::Raylib::RaylibTexture2DResourceManager raylibTexture2DResourceManager;
	};
}
