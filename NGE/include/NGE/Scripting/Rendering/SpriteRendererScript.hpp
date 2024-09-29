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

namespace NGE::Scripting::Rendering {
	class SpriteRendererScript : public Script {
	public:

		NGE_API SpriteRendererScript(NGE::SceneManagement::Node* node);

		NGE_API const std::shared_ptr<NGE::Rendering::RenderingContextElement>& GetRenderingContextElement() const noexcept;
		NGE_API std::shared_ptr<NGE::Rendering::RenderingContextElement>& GetRenderingContextElement() noexcept;
		NGE_API const NGE::ResourceManagement::ResourceID& GetResourceID() const noexcept;
		NGE_API NGE::ResourceManagement::ResourceID& GetResourcePath(NGE::ResourceManagement::ResourceID& result) const;
		NGE_API void SetResourceID(const NGE::ResourceManagement::ResourceID& resourceID);
		NGE_API void SetResourceID(NGE::ResourceManagement::ResourceID&& resourceID) noexcept;
		NGE_API const NGE::Math::Rectangle<float>& GetSourceRectangle() const noexcept;
		NGE_API void SetSourceRectangle(const NGE::Math::Rectangle<float>& sourceRectangle) noexcept;
		NGE_API const NGE::Math::Vector2<float>& GetPivot() const noexcept;
		NGE_API void SetPivot(const NGE::Math::Vector2<float>& pivot) noexcept;
		NGE_API const NGE::Rendering::Color<std::uint8_t>& GetColor() const noexcept;
		NGE_API void SetColor(const NGE::Rendering::Color<std::uint8_t>& color) noexcept;
		NGE_API unsigned int GetLayerIndex() const noexcept;
		NGE_API void SetLayerIndex(unsigned int layerIndex) noexcept;

	protected:

		NGE_API virtual void OnFrameRender(NGE::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime) override;
	
	private:

		std::shared_ptr<NGE::Rendering::RenderingContextElement> renderingContextElement;
	};
}
