#include <chrono>
#include <memory>
#include <print>
#include <stack>
#include <vector>

#include <NGE/Engine.hpp>
#include <NGE/Hashing/StringHash.hpp>
#include <NGE/InputSystem/InputEvent.hpp>
#include <NGE/Math/Vector2.hpp>
#include <NGE/SceneManagement/Node.hpp>
#include <NGE/Scripting/Script.hpp>
#include <NGE/Scripting/UI/CanvasScript.hpp>
#include <NGE/Scripting/UI/UIElementNodeTraversalData.hpp>
#include <NGE/Scripting/UI/UIElementScript.hpp>

using namespace NGE;
using namespace NGE::Hashing;
using namespace NGE::InputSystem;
using namespace NGE::Math;
using namespace NGE::SceneManagement;
using namespace NGE::Scripting;
using namespace NGE::Scripting::UI;
using namespace std;
using namespace std::chrono;

const StringHash CanvasScript::mousePositionNameHash("Mouse.Position");
const InputEvent CanvasScript::uiCursorPositionInputEvent("UI.Cursor.Position");

CanvasScript::CanvasScript(Node* node) :
	Script(node),
	isRebuildingChildNodeCache(true),
	childAddedObserverID(node->OnChildAdded.AddObserver([&](const shared_ptr<Node>& node) { isRebuildingChildNodeCache = true; })),
	childRemovedObserverID(node->OnChildRemoved.AddObserver([&](const shared_ptr<Node>& node) { isRebuildingChildNodeCache = true; })),
	scriptAddedObserverID(node->OnScriptAdded.AddObserver([&](const shared_ptr<Script>& script) { UpdateRebuildingChildNodeCacheState(script); })),
	scriptRemovedObserverID(node->OnScriptRemoved.AddObserver([&](const shared_ptr<Script>& script) { UpdateRebuildingChildNodeCacheState(script); })) {
	// ...
}

CanvasScript::~CanvasScript() {
	Node& node(GetNode());
	node.OnChildAdded -= childAddedObserverID;
	node.OnChildRemoved -= childRemovedObserverID;
	node.OnScriptAdded -= scriptAddedObserverID;
	node.OnScriptRemoved -= scriptRemovedObserverID;
}

void CanvasScript::OnFrameRender(Engine& game, high_resolution_clock::duration deltaTime) {
	if (isRebuildingChildNodeCache) {
		isRebuildingChildNodeCache = false;
		stack<UIElementNodeTraversalData> node_stack;
		node_stack.push({ &GetNode(), false });
		while (!node_stack.empty()) {
			if (node_stack.top().hasChildrenListed) {
				shared_ptr<UIElementScript> ui_element;
				if (node_stack.top().node->TryGettingScript<UIElementScript>(ui_element)) {
					cachedUIElements.push_back(ui_element);
				}
				node_stack.pop();
			}
			else {
				node_stack.top().hasChildrenListed = true;
				for (const auto& child_node : node_stack.top().node->GetChildren()) {
					node_stack.push({ child_node.get(), false });
				}
			}
		}
	}
	for (const auto& input_event : game.GetCurrentInputEvents()) {
		if (input_event.GetNameHash() == mousePositionNameHash) {
			Vector2<float> mouse_position(input_event.GetPressValue2D());
			for (const auto& ui_element : cachedUIElements) {
				ui_element->ApplyInputEvent(InputEvent(uiCursorPositionInputEvent, mouse_position));
			}
		}
	}
}

void CanvasScript::UpdateRebuildingChildNodeCacheState(const shared_ptr<Script>& script) {
	if (dynamic_cast<UIElementScript*>(script.get())) {
		isRebuildingChildNodeCache = true;
	}
}
