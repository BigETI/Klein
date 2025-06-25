#include <string>

#include <Klein/Math/Bounds.hpp>
#include <Klein/Math/EAlignment.hpp>
#include <Klein/Rendering/Color.hpp>
#include <Klein/Rendering/RenderingContext.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>
#include <Klein/Scripting/UI/ImageScript.hpp>

using namespace std;

using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::ResourceManagement;
using namespace Klein::Scripting::UI;

ImageScript::ImageScript(Klein::SceneManagement::Node* node) :
	UIElementScript(node),
	renderingContextElement(
		make_shared<RenderingContextElement>(
			true,
			false,
			string(),
			string(),
			Rectangle<float>(Vector2<float>(0.0f, 0.0f), Vector2<float>(1.0f, 1.0f)),
			Rectangle<float>(Vector2<float>(0.0f, 0.0f), Vector2<float>(1.0f, 1.0f)),
			0.0f,
			Vector2<float>(0.0f, 0.0f),
			Color<float>(1.0f, 1.0f, 1.0f, 1.0f),
			string(),
			1.0f,
			0.2f,
			0U
		)
	) {
	// ...
}

const ResourceID& ImageScript::GetImageResourceID() const noexcept {
	return renderingContextElement->GetTexture2DResourceID();
}

void ImageScript::SetImageResourceID(const ResourceID& imageResourceID) {
	renderingContextElement->SetTexture2DResourceID(imageResourceID);
}

const Color<float>& ImageScript::GetColor() const noexcept {
	return renderingContextElement->GetColor();
}

void ImageScript::SetColor(const Color<float>& color) noexcept {
	renderingContextElement->SetColor(color);
}

void ImageScript::OnUIRender(RenderingContext& renderingContext, const Bounds<float>& bounds) {
	renderingContextElement->SetRectangle(bounds.GetRectangle(EAlignment::TopLeft));
	renderingContext.StageElement(renderingContextElement);
}
