#pragma once

#include <memory>

#include "../../Exportables/Exportable.hxx"
#include "../../Math/Bounds.hpp"
#include "../../Rendering/Color.hpp"
#include "../../Rendering/RenderingContext.hpp"
#include "../../Rendering/RenderingContextElement.hpp"
#include "../../ResourceManagement/ResourceID.hpp"
#include "../../SceneManagement/Node.hpp"
#include "UIElementScript.hpp"

namespace Klein::Scripting::UI {
	class ImageScript : public UIElementScript {
	public:
		KLEIN_API ImageScript(Klein::SceneManagement::Node* node);

		KLEIN_API const Klein::ResourceManagement::ResourceID& GetImageResourceID() const noexcept;
		KLEIN_API void SetImageResourceID(const Klein::ResourceManagement::ResourceID& imageResourceID);
		KLEIN_API const Klein::Rendering::Color<float>& GetColor() const noexcept;
		KLEIN_API void SetColor(const Klein::Rendering::Color<float>& color) noexcept;
		KLEIN_API virtual void OnUIRender(Klein::Rendering::RenderingContext& renderingContext, const Klein::Math::Bounds<float>& bounds) override;

	private:

		std::shared_ptr<Klein::Rendering::RenderingContextElement> renderingContextElement;
	};
}
