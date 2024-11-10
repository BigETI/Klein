#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>

#include "../../Exportables/Exportable.hxx"
#include "../../Engine.hpp"
#include "../../Math/Vector2.hpp"
#include "../../Rendering/Color.hpp"
#include "../../Rendering/RenderingContextElement.hpp"
#include "../../ResourceManagement/ResourceID.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"

namespace Klein::Scripting::Rendering {
	class SpriteRendererScript : public Script {
	public:

		KLEIN_API SpriteRendererScript(Klein::SceneManagement::Node* node);

		KLEIN_API const std::shared_ptr<Klein::Rendering::RenderingContextElement>& GetRenderingContextElement() const noexcept;
		KLEIN_API std::shared_ptr<Klein::Rendering::RenderingContextElement>& GetRenderingContextElement() noexcept;
		KLEIN_API const Klein::ResourceManagement::ResourceID& GetResourceID() const noexcept;
		KLEIN_API Klein::ResourceManagement::ResourceID& GetResourcePath(Klein::ResourceManagement::ResourceID& result) const;
		KLEIN_API void SetResourceID(const Klein::ResourceManagement::ResourceID& resourceID);
		KLEIN_API void SetResourceID(Klein::ResourceManagement::ResourceID&& resourceID) noexcept;
		KLEIN_API const Klein::Math::Rectangle<float>& GetSourceRectangle() const noexcept;
		KLEIN_API void SetSourceRectangle(const Klein::Math::Rectangle<float>& sourceRectangle) noexcept;
		KLEIN_API const Klein::Math::Vector2<float>& GetPivot() const noexcept;
		KLEIN_API void SetPivot(const Klein::Math::Vector2<float>& pivot) noexcept;
		KLEIN_API const Klein::Rendering::Color<std::uint8_t>& GetColor() const noexcept;
		KLEIN_API void SetColor(const Klein::Rendering::Color<std::uint8_t>& color) noexcept;
		KLEIN_API unsigned int GetLayerIndex() const noexcept;
		KLEIN_API void SetLayerIndex(unsigned int layerIndex) noexcept;

	protected:

		KLEIN_API virtual void OnFrameRender(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime) override;

	private:

		std::shared_ptr<Klein::Rendering::RenderingContextElement> renderingContextElement;
	};
}
