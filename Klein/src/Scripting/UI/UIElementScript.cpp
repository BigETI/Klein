#include <cmath>

#include <Klein/InputSystem/InputEvent.hpp>
#include <Klein/Math/Border.hpp>
#include <Klein/Math/Bounds.hpp>
#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/RenderingContext.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Script.hpp>
#include <Klein/Scripting/UI/UIElementScript.hpp>

using namespace std;

using namespace Klein::InputSystem;
using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting::UI;

UIElementScript::UIElementScript(Node* node) : Script(node) {
	// ...
}

UIElementScript::~UIElementScript() noexcept {
	// ...
}

const Vector2<float>& UIElementScript::GetPosition() const noexcept {
	return position;
}

void UIElementScript::SetPosition(const Vector2<float>& position) noexcept {
	this->position = position;
}

void UIElementScript::SetPosition(Vector2<float>&& position) noexcept {
	this->position = position;
}

const Bounds<float>& UIElementScript::GetAnchor() const noexcept {
	return anchor;
}

void UIElementScript::SetAnchor(const Bounds<float>& anchor) noexcept {
	this->anchor = anchor;
}

void UIElementScript::SetAnchor(Bounds<float>&& anchor) noexcept {
	this->anchor = anchor;
}

const Border<float>& UIElementScript::GetBorder() const noexcept {
	return border;
}

void UIElementScript::SetBorder(const Border<float>& border) noexcept {
	this->border = border;
}

void UIElementScript::SetBorder(Border<float>&& border) noexcept {
	this->border = border;
}

const Border<float>& UIElementScript::GetMargin() const noexcept {
	return margin;
}

void UIElementScript::SetMargin(const Border<float>& margin) noexcept {
	this->margin = margin;
}

void UIElementScript::SetMargin(Border<float>&& margin) noexcept {
	this->margin = margin;
}

const Border<float>& UIElementScript::GetPadding() const noexcept {
	return padding;
}

void UIElementScript::SetPadding(const Border<float>& padding) noexcept {
	this->padding = padding;
}

void UIElementScript::SetPadding(Border<float>&& padding) noexcept {
	this->padding = padding;
}

bool UIElementScript::ConsumeInputEvent(const InputEvent& inputEvent) {
	return false;
}

void UIElementScript::OnUIRender(RenderingContext& renderingContext, const Bounds<float>& bounds) {
	// ...
}
