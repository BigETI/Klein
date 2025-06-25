#include <Klein/Hashing/StringHash.hpp>
#include <Klein/InputSystem/InputEvent.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/UI/ButtonScript.hpp>
#include <Klein/Scripting/UI/ImageScript.hpp>

using namespace Klein::Hashing;
using namespace Klein::InputSystem;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting::UI;

static const StringHash uiCursorPressingInputEventStringHash("UI.Cursor.Pressing");

ButtonScript::ButtonScript(Node* node) : ImageScript(node) {
	// ...
}

bool ButtonScript::ConsumeInputEvent(const InputEvent& inputEvent) {
	if ((inputEvent.GetNameHash() == uiCursorPressingInputEventStringHash) && inputEvent.IsPressing()) {
		OnClicked();
	}
	return true;
}
