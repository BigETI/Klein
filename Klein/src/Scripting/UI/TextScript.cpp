#include <memory>
#include <string>

#include <Klein/Math/Bounds.hpp>
#include <Klein/Math/Rectangle.hpp>
#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/Color.hpp>
#include <Klein/Rendering/RenderingContext.hpp>
#include <Klein/Rendering/RenderingContextElement.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>
#include <Klein/Scripting/UI/TextScript.hpp>
#include <Klein/Scripting/UI/UIElementScript.hpp>

using namespace std;

using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::ResourceManagement;
using namespace Klein::Scripting::UI;

TextScript::TextScript(Klein::SceneManagement::Node* node) :
	UIElementScript(node),
	renderingContextElement(
		make_shared<RenderingContextElement>(
			false,
			true,
			string(),
			string(),
			Rectangle<float>(Vector2<float>(0.0f, 0.0f), Vector2<float>(1.0f, 1.0f)),
			Rectangle<float>(Vector2<float>(0.0f, 0.0f), Vector2<float>(1.0f, 1.0f)),
			0.0f,
			Vector2<float>(0.0f, 0.0f),
			Color<float>(1.0f, 1.0f, 1.0f, 1.0f),
			string(),
			12.0f,
			12.0f * 0.2f,
			0U
		)
	) {
	// ...
}

const ResourceID& TextScript::GetFontResourceID() const noexcept {
	return renderingContextElement->GetFontResourceID();
}

void TextScript::SetFontResourceID(const ResourceID& fontResourceID) {
}

const string& TextScript::GetText() const noexcept {
	return renderingContextElement->GetText();
}

void TextScript::SetText(const string& text) {
	renderingContextElement->SetText(text);
}

float TextScript::GetTextFontSize() const noexcept {
	return renderingContextElement->GetTextFontSize();
}

void TextScript::SetTextFontSize(float textFontSize) noexcept {
	renderingContextElement->SetTextFontSize(textFontSize);
}

float TextScript::GetTextSpacing() const noexcept {
	return renderingContextElement->GetTextSpacing();
}

void TextScript::SetTextSpacing(float textSpacing) noexcept {
	renderingContextElement->SetTextSpacing(textSpacing);
}

const Color<float>& TextScript::GetColor() const noexcept {
	return renderingContextElement->GetColor();
}

void TextScript::SetColor(const Color<float>& color) noexcept {
	renderingContextElement->SetColor(color);
}

void TextScript::OnUIRender(RenderingContext& renderingContext, const Bounds<float>& bounds) {
	renderingContextElement->SetRectangle(bounds.GetRectangle(EAlignment::TopLeft));
	renderingContext.StageElement(renderingContextElement);
}