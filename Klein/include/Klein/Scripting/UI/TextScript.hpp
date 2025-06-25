#pragma once

#include <memory>
#include <string>

#include "../../Exportables/Exportable.hxx"
#include "../../Math/Bounds.hpp"
#include "../../Rendering/Color.hpp"
#include "../../Rendering/RenderingContext.hpp"
#include "../../Rendering/RenderingContextElement.hpp"
#include "../../ResourceManagement/ResourceID.hpp"
#include "../../SceneManagement/Node.hpp"
#include "UIElementScript.hpp"

namespace Klein::Scripting::UI {
	class TextScript : public UIElementScript {
	public:

		KLEIN_API TextScript(Klein::SceneManagement::Node* node);

		KLEIN_API const Klein::ResourceManagement::ResourceID& GetFontResourceID() const noexcept;
		KLEIN_API void SetFontResourceID(const Klein::ResourceManagement::ResourceID& fontResourceID);
		KLEIN_API const std::string& GetText() const noexcept;
		KLEIN_API void SetText(const std::string& text);
		KLEIN_API float GetTextFontSize() const noexcept;
		KLEIN_API void SetTextFontSize(float textFontSize) noexcept;
		KLEIN_API float GetTextSpacing() const noexcept;
		KLEIN_API void SetTextSpacing(float textSpacing) noexcept;
		KLEIN_API const Klein::Rendering::Color<float>& GetColor() const noexcept;
		KLEIN_API void SetColor(const Klein::Rendering::Color<float>& color) noexcept;
		KLEIN_API virtual void OnUIRender(Klein::Rendering::RenderingContext& renderingContext, const Klein::Math::Bounds<float>& bounds) override;

	private:

		std::shared_ptr<Klein::Rendering::RenderingContextElement> renderingContextElement;
	};
}
