#include <chrono>
#include <cstddef>
#include <memory>

#include <Klein/Engine.hpp>
#include <Klein/Hashing/StringHash.hpp>
#include <Klein/InputSystem/InputEvent.hpp>
#include <Klein/Math/Bounds.hpp>
#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/IRenderer.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Rendering/RenderingContextScript.hpp>
#include <Klein/Scripting/UI/CanvasScript.hpp>
#include <Klein/Scripting/UI/UIElementNodeTraversalData.hpp>
#include <Klein/Scripting/UI/UIElementScript.hpp>

using namespace std;
using namespace std::chrono;

using namespace Klein;
using namespace Klein::Hashing;
using namespace Klein::InputSystem;
using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting::Rendering;
using namespace Klein::Scripting::UI;

static const StringHash mousePositionStringHash("Mouse.Position");
static const StringHash mouseButtonZeroStringHash("Mouse.Button.0");
static const InputEvent uiCursorPositionInputEvent("UI.Cursor.Position");
static const InputEvent uiCursorPressingInputEvent("UI.Cursor.Pressing");
static const InputEvent uiCursorReleasingInputEvent("UI.Cursor.Releasing");

CanvasScript::CanvasScript(Node* node) : RenderingContextScript(node) {
	// ...
}

void CanvasScript::OnFrameRender(Engine& engine, const high_resolution_clock::duration& deltaTime) {
	if (engine.GetRenderers().size() <= static_cast<size_t>(0)) {
		return;
	}
	shared_ptr<IRenderer> renderer(engine.GetRenderers().at(static_cast<size_t>(0)));
	Bounds<float> bounds(renderer->GetHeight(), 0.0f, 0.0f, renderer->GetWidth());
	for (const auto& input_event : engine.GetCurrentInputEvents()) {
		if (input_event.GetNameHash() == mousePositionStringHash) {
			Vector2<float> mouse_position(input_event.GetPressValue2D());
			lastUICursorPosition = Vector2<float>(mouse_position.x, renderer->GetHeight() - mouse_position.y);
			ForwardInputEventToNode(InputEvent(uiCursorPositionInputEvent, lastUICursorPosition), GetNode(), bounds);
		}
		if (input_event.GetNameHash() == mouseButtonZeroStringHash) {
			if (input_event.IsPressing()) {
				ForwardInputEventToNode(InputEvent(uiCursorPressingInputEvent, lastUICursorPosition), GetNode(), bounds);
			}
			else {
				ForwardInputEventToNode(InputEvent(uiCursorReleasingInputEvent, lastUICursorPosition), GetNode(), bounds);
			}
		}
	}
	EnsureRenderingContext(engine);
	RenderingContext& rendering_context(EnsureRenderingContext(engine));
	rendering_context.SetCameraAlignment(Vector2<float>(0.0f, 1.0f));
	RenderUINode(rendering_context, GetNode(), bounds);
}

Bounds<float> CanvasScript::GetOuterBounds(const UIElementScript& uiElement, const Bounds<float>& parentBounds) noexcept {
	const Bounds<float>& anchor(uiElement.GetAnchor());
	return Bounds<float>(
		lerp(parentBounds.bottom, parentBounds.top, anchor.top),
		lerp(parentBounds.bottom, parentBounds.top, anchor.bottom),
		lerp(parentBounds.left, parentBounds.right, anchor.left),
		lerp(parentBounds.left, parentBounds.right, anchor.right)
	) + uiElement.GetPosition() + uiElement.GetBorder() - uiElement.GetMargin();
}

bool CanvasScript::ForwardInputEventToNode(const InputEvent& inputEvent, Node& node, const Bounds<float>& parentBounds) {
	shared_ptr<UIElementScript> ui_element;
	Bounds<float> outer_bounds;
	Bounds<float> inner_bounds;
	if (node.TryGettingScript<UIElementScript>(ui_element)) {
		outer_bounds = GetOuterBounds(*ui_element, parentBounds);
		inner_bounds = outer_bounds - ui_element->GetPadding();
	}
	else {
		outer_bounds = parentBounds;
		inner_bounds = parentBounds;
	}
	bool has_not_consumed_event(true);
	for (const auto& child : node.GetChildren()) {
		if (ForwardInputEventToNode(inputEvent, *child, inner_bounds)) {
			has_not_consumed_event = false;
			break;
		}
	}
	return has_not_consumed_event && ui_element && outer_bounds.IsContained(inputEvent.GetPressValue2D()) && ui_element->ConsumeInputEvent(inputEvent);
}

void CanvasScript::RenderUINode(RenderingContext& renderingContext, Node& node, const Bounds<float>& parentBounds) {
	shared_ptr<UIElementScript> ui_element;
	if (node.TryGettingScript<UIElementScript>(ui_element)) {
		Bounds<float> outer_bounds(GetOuterBounds(*ui_element, parentBounds));
		ui_element->OnUIRender(renderingContext, outer_bounds);
		Bounds<float> inner_bounds(outer_bounds - ui_element->GetPadding());
		for (const auto& child : node.GetChildren()) {
			RenderUINode(renderingContext, *child, inner_bounds);
		}
	}
	else {
		for (const auto& child : node.GetChildren()) {
			RenderUINode(renderingContext, *child, parentBounds);
		}
	}
}
