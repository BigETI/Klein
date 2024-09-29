#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include "../Exportables/Exportable.hxx"
#include "../Math/Rectangle.hpp"
#include "../Math/Vector2.hpp"
#include "../Rendering/Color.hpp"
#include "../ResourceManagement/ResourceID.hpp"

namespace NGE::Rendering {
	class RenderingContextElement {
	public:

		NGE_API RenderingContextElement();
		NGE_API RenderingContextElement(
			const NGE::ResourceManagement::ResourceID& resourceID,
			const NGE::Math::Rectangle<float>& sourceRectangle,
			const NGE::Math::Vector2<float>& position,
			float rotation,
			const NGE::Math::Vector2<float>& size,
			const NGE::Math::Vector2<float>& pivot,
			const NGE::Rendering::Color<std::uint8_t>& color,
			unsigned int layerIndex
		);
		NGE_API RenderingContextElement(
			NGE::ResourceManagement::ResourceID&& resourceID,
			NGE::Math::Rectangle<float>&& sourceRectangle,
			NGE::Math::Vector2<float>&& position,
			float rotation,
			NGE::Math::Vector2<float>&& size,
			NGE::Math::Vector2<float>&& pivot,
			NGE::Rendering::Color<std::uint8_t>&& color,
			unsigned int layerIndex
		) noexcept;
		NGE_API RenderingContextElement(const RenderingContextElement& renderingContextElement);
		NGE_API RenderingContextElement(RenderingContextElement&& renderingContextElement) noexcept;

		NGE_API const NGE::ResourceManagement::ResourceID& GetResourceID() const noexcept;
		NGE_API NGE::ResourceManagement::ResourceID& GetResourceID(NGE::ResourceManagement::ResourceID& result) const;
		NGE_API void SetResourceID(const NGE::ResourceManagement::ResourceID& resourceID);
		NGE_API void SetResourceID(NGE::ResourceManagement::ResourceID&& resourceID) noexcept;
		NGE_API const NGE::Math::Rectangle<float>& GetSourceRectangle() const noexcept;
		NGE_API void SetSourceRectangle(const NGE::Math::Rectangle<float>& sourceRectangle) noexcept;
		NGE_API const NGE::Math::Vector2<float>& GetPosition() const noexcept;
		NGE_API void SetPosition(const NGE::Math::Vector2<float>& position) noexcept;
		NGE_API float GetRotation() const noexcept;
		NGE_API void SetRotation(float rotation) noexcept;
		NGE_API const NGE::Math::Vector2<float>& GetSize() const noexcept;
		NGE_API void SetSize(const NGE::Math::Vector2<float>& size) noexcept;
		NGE_API const NGE::Math::Vector2<float>& GetPivot() const noexcept;
		NGE_API void SetPivot(const NGE::Math::Vector2<float>& pivot) noexcept;
		NGE_API const NGE::Rendering::Color<std::uint8_t>& GetColor() const noexcept;
		NGE_API void SetColor(const NGE::Rendering::Color<std::uint8_t>& color) noexcept;
		NGE_API unsigned int GetLayerIndex() const noexcept;
		NGE_API void SetLayerIndex(unsigned int layerIndex) noexcept;

		NGE_API RenderingContextElement& operator =(const RenderingContextElement& renderingContextElement);
		NGE_API RenderingContextElement& operator =(RenderingContextElement&& renderingContextElement) noexcept;
		NGE_API bool operator ==(const RenderingContextElement& renderingContextElement) const noexcept;
		NGE_API bool operator <(const RenderingContextElement& renderingContextElement) const noexcept;
		NGE_API bool operator <=(const RenderingContextElement& renderingContextElement) const noexcept;
		NGE_API bool operator >(const RenderingContextElement& renderingContextElement) const noexcept;
		NGE_API bool operator >=(const RenderingContextElement& renderingContextElement) const noexcept;

	private:

		NGE::ResourceManagement::ResourceID resourceID;
		NGE::Math::Rectangle<float> sourceRectangle;
		NGE::Math::Vector2<float> position;
		float rotation;
		NGE::Math::Vector2<float> size;
		NGE::Math::Vector2<float> pivot;
		NGE::Rendering::Color<std::uint8_t> color;
		unsigned int layerIndex;
	};
}

template <>
struct std::less<std::shared_ptr<NGE::Rendering::RenderingContextElement>> {
	constexpr bool operator ()(
		const std::shared_ptr<NGE::Rendering::RenderingContextElement>& lhs,
		const std::shared_ptr<NGE::Rendering::RenderingContextElement>& rhs) const noexcept {
		return rhs && (!lhs || (*lhs < *rhs));
	}
};
