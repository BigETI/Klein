#pragma once

#include <functional>
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
			bool isTexture2DVisible,
			bool isTextVisible,
			const Klein::ResourceManagement::ResourceID& texture2DResourceID,
			const Klein::ResourceManagement::ResourceID& fontResourceID,
			const Klein::Math::Rectangle<float>& texture2DSourceRectangle,
			const Klein::Math::Rectangle<float>& rectangle,
			float rotation,
			const Klein::Math::Vector2<float>& pivot,
			const Klein::Rendering::Color<float>& color,
			const std::string& text,
			float textFontSize,
			float textSpacing,
			unsigned int layerIndex
		);
		KLEIN_API RenderingContextElement(
			bool isTexture2DVisible,
			bool isTextVisible,
			Klein::ResourceManagement::ResourceID&& texture2DResourceID,
			Klein::ResourceManagement::ResourceID&& fontResourceID,
			Klein::Math::Rectangle<float>&& texture2DSourceRectangle,
			Klein::Math::Rectangle<float>&& rectangle,
			float rotation,
			Klein::Math::Vector2<float>&& pivot,
			Klein::Rendering::Color<float>&& color,
			std::string&& text,
			float textFontSize,
			float textSpacing,
			unsigned int layerIndex
		) noexcept;
		KLEIN_API RenderingContextElement(const RenderingContextElement& renderingContextElement);
		KLEIN_API RenderingContextElement(RenderingContextElement&& renderingContextElement) noexcept;

		KLEIN_API bool IsTexture2DVisible() const noexcept;
		KLEIN_API void SetTexture2DVisibility(bool isTexture2DVisible) noexcept;
		KLEIN_API bool IsTextVisible() const noexcept;
		KLEIN_API void SetTextVisibility(bool isTextVisible) noexcept;
		KLEIN_API const Klein::ResourceManagement::ResourceID& GetTexture2DResourceID() const noexcept;
		KLEIN_API Klein::ResourceManagement::ResourceID& GetTexture2DResourceID(Klein::ResourceManagement::ResourceID& result) const;
		KLEIN_API void SetTexture2DResourceID(const Klein::ResourceManagement::ResourceID& texture2DResourceID);
		KLEIN_API void SetTexture2DResourceID(Klein::ResourceManagement::ResourceID&& texture2DResourceID) noexcept;
		KLEIN_API const Klein::ResourceManagement::ResourceID& GetFontResourceID() const noexcept;
		KLEIN_API Klein::ResourceManagement::ResourceID& GetFontResourceID(Klein::ResourceManagement::ResourceID& result) const;
		KLEIN_API void SetFontResourceID(const Klein::ResourceManagement::ResourceID& fontResourceID);
		KLEIN_API void SetFontResourceID(Klein::ResourceManagement::ResourceID&& fontResourceID) noexcept;
		KLEIN_API const Klein::Math::Rectangle<float>& GetTexture2DSourceRectangle() const noexcept;
		KLEIN_API void SetTexture2DSourceRectangle(const Klein::Math::Rectangle<float>& texture2DSourceRectangle) noexcept;
		KLEIN_API const Klein::Math::Rectangle<float>& GetRectangle() const noexcept;
		KLEIN_API void SetRectangle(const Klein::Math::Rectangle<float>& rectangle) noexcept;
		KLEIN_API float GetRotation() const noexcept;
		KLEIN_API void SetRotation(float rotation) noexcept;
		KLEIN_API const Klein::Math::Vector2<float>& GetPivot() const noexcept;
		KLEIN_API void SetPivot(const Klein::Math::Vector2<float>& pivot) noexcept;
		KLEIN_API const Klein::Rendering::Color<float>& GetColor() const noexcept;
		KLEIN_API void SetColor(const Klein::Rendering::Color<float>& color) noexcept;
		KLEIN_API const std::string& GetText() const noexcept;
		KLEIN_API std::string& GetText(std::string& result) const;
		KLEIN_API void SetText(const std::string& text);
		KLEIN_API void SetText(std::string&& text) noexcept;
		KLEIN_API float GetTextFontSize() const noexcept;
		KLEIN_API void SetTextFontSize(float textFontSize) noexcept;
		KLEIN_API float GetTextSpacing() const noexcept;
		KLEIN_API void SetTextSpacing(float textSpacing) noexcept;
		KLEIN_API void SetLayerIndex(unsigned int layerIndex) noexcept;
		KLEIN_API unsigned int GetLayerIndex() const noexcept;

		KLEIN_API RenderingContextElement& operator =(const RenderingContextElement& renderingContextElement);
		KLEIN_API RenderingContextElement& operator =(RenderingContextElement&& renderingContextElement) noexcept;
		KLEIN_API bool operator ==(const RenderingContextElement& renderingContextElement) const noexcept;
		KLEIN_API bool operator <(const RenderingContextElement& renderingContextElement) const noexcept;
		KLEIN_API bool operator <=(const RenderingContextElement& renderingContextElement) const noexcept;
		KLEIN_API bool operator >(const RenderingContextElement& renderingContextElement) const noexcept;
		KLEIN_API bool operator >=(const RenderingContextElement& renderingContextElement) const noexcept;

	private:

		bool isTexture2DVisible;
		bool isTextVisible;
		Klein::ResourceManagement::ResourceID texture2DResourceID;
		Klein::ResourceManagement::ResourceID fontResourceID;
		Klein::Math::Rectangle<float> texture2DSourceRectangle;
		Klein::Math::Rectangle<float> rectangle;
		float rotation;
		Klein::Math::Vector2<float> pivot;
		Klein::Rendering::Color<float> color;
		std::string text;
		float textFontSize;
		float textSpacing;
		unsigned int layerIndex;
	};
}

template <>
struct std::less<std::shared_ptr<Klein::Rendering::RenderingContextElement>> {
#ifndef IS_KLEIN_CXX_STD_17
	constexpr
#endif
	bool operator ()(
		const std::shared_ptr<Klein::Rendering::RenderingContextElement>& lhs,
		const std::shared_ptr<Klein::Rendering::RenderingContextElement>& rhs) const noexcept {
		return rhs && (!lhs || (*lhs < *rhs));
	}
};
