#include <Klein/InputSystem/InputEvent.hpp>
#include <Klein/Math/Bounds.hpp>
#include <Klein/Math/Rectangle.hpp>
#include <Klein/Math/Vector2.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Script.hpp>
#include <Klein/Scripting/UI/UIElementScript.hpp>

using namespace Klein::InputSystem;
using namespace Klein::Math;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting::UI;

UIElementScript::UIElementScript(Node* node) : Script(node) {
	// ...
}

UIElementScript::~UIElementScript() noexcept {
	// ...
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

const Bounds<float>& UIElementScript::GetBounds() const noexcept {
	return bounds;
}

void UIElementScript::SetBounds(const Bounds<float>& bounds) noexcept {
	this->bounds = bounds;
}

void UIElementScript::SetBounds(Bounds<float>&& bounds) noexcept {
	this->bounds = bounds;
}

const Bounds<float>& UIElementScript::GetMargin() const noexcept {
	return margin;
}

void UIElementScript::SetMargin(const Bounds<float>& margin) noexcept {
	this->margin = margin;
}

void UIElementScript::SetMargin(Bounds<float>&& margin) noexcept {
	this->margin = margin;
}

Rectangle<float> UIElementScript::GetAbsoluteRectangle(const Rectangle<float>& relativeToRectangle) const noexcept {
	// TODO: Calculate rectangle, using anchor, bounds, and margin!
	return Rectangle<float>();
}

bool UIElementScript::ApplyInputEvent(const InputEvent& inputEvent) {
	// TODO: Use input element attributes, to apply input events upon them.
	return false;
}
