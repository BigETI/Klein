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

namespace Klein::Rendering {
	class RenderingContextElement {
	public:

		KLEIN_API RenderingContextElement();
		KLEIN_API RenderingContextElement(
			const Klein::ResourceManagement::ResourceID& resourceID,
			const Klein::Math::Rectangle<float>& sourceRectangle,
			const Klein::Math::Vector2<float>& position,
			float rotation,
			const Klein::Math::Vector2<float>& size,
			const Klein::Math::Vector2<float>& pivot,
			const Klein::Rendering::Color<std::uint8_t>& color,
			unsigned int layerIndex
		);
		KLEIN_API RenderingContextElement(
			Klein::ResourceManagement::ResourceID&& resourceID,
			Klein::Math::Rectangle<float>&& sourceRectangle,
			Klein::Math::Vector2<float>&& position,
			float rotation,
			Klein::Math::Vector2<float>&& size,
			Klein::Math::Vector2<float>&& pivot,
			Klein::Rendering::Color<std::uint8_t>&& color,
			unsigned int layerIndex
		) noexcept;
		KLEIN_API RenderingContextElement(const RenderingContextElement& renderingContextElement);
		KLEIN_API RenderingContextElement(RenderingContextElement&& renderingContextElement) noexcept;

		KLEIN_API const Klein::ResourceManagement::ResourceID& GetResourceID() const noexcept;
		KLEIN_API Klein::ResourceManagement::ResourceID& GetResourceID(Klein::ResourceManagement::ResourceID& result) const;
		KLEIN_API void SetResourceID(const Klein::ResourceManagement::ResourceID& resourceID);
		KLEIN_API void SetResourceID(Klein::ResourceManagement::ResourceID&& resourceID) noexcept;
		KLEIN_API const Klein::Math::Rectangle<float>& GetSourceRectangle() const noexcept;
		KLEIN_API void SetSourceRectangle(const Klein::Math::Rectangle<float>& sourceRectangle) noexcept;
		KLEIN_API const Klein::Math::Vector2<float>& GetPosition() const noexcept;
		KLEIN_API void SetPosition(const Klein::Math::Vector2<float>& position) noexcept;
		KLEIN_API float GetRotation() const noexcept;
		KLEIN_API void SetRotation(float rotation) noexcept;
		KLEIN_API const Klein::Math::Vector2<float>& GetSize() const noexcept;
		KLEIN_API void SetSize(const Klein::Math::Vector2<float>& size) noexcept;
		KLEIN_API const Klein::Math::Vector2<float>& GetPivot() const noexcept;
		KLEIN_API void SetPivot(const Klein::Math::Vector2<float>& pivot) noexcept;
		KLEIN_API const Klein::Rendering::Color<std::uint8_t>& GetColor() const noexcept;
		KLEIN_API void SetColor(const Klein::Rendering::Color<std::uint8_t>& color) noexcept;
		KLEIN_API unsigned int GetLayerIndex() const noexcept;
		KLEIN_API void SetLayerIndex(unsigned int layerIndex) noexcept;

		KLEIN_API RenderingContextElement& operator =(const RenderingContextElement& renderingContextElement);
		KLEIN_API RenderingContextElement& operator =(RenderingContextElement&& renderingContextElement) noexcept;
		KLEIN_API bool operator ==(const RenderingContextElement& renderingContextElement) const noexcept;
		KLEIN_API bool operator <(const RenderingContextElement& renderingContextElement) const noexcept;
		KLEIN_API bool operator <=(const RenderingContextElement& renderingContextElement) const noexcept;
		KLEIN_API bool operator >(const RenderingContextElement& renderingContextElement) const noexcept;
		KLEIN_API bool operator >=(const RenderingContextElement& renderingContextElement) const noexcept;

	private:

		Klein::ResourceManagement::ResourceID resourceID;
		Klein::Math::Rectangle<float> sourceRectangle;
		Klein::Math::Vector2<float> position;
		float rotation;
		Klein::Math::Vector2<float> size;
		Klein::Math::Vector2<float> pivot;
		Klein::Rendering::Color<std::uint8_t> color;
		unsigned int layerIndex;
	};
}

template <>
struct std::less<std::shared_ptr<Klein::Rendering::RenderingContextElement>> {
	constexpr bool operator ()(
		const std::shared_ptr<Klein::Rendering::RenderingContextElement>& lhs,
		const std::shared_ptr<Klein::Rendering::RenderingContextElement>& rhs) const noexcept {
		return rhs && (!lhs || (*lhs < *rhs));
	}
};
