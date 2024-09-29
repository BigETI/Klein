#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include <raylib.h>

#include <NGE/InputSystem/InputEvent.hpp>
#include <NGE/InputSystem/Raylib/RaylibGamepadInputEvents.hpp>
#include <NGE/InputSystem/Raylib/RaylibInputHandler.hpp>
#include <NGE/Math/Vector2.hpp>

using namespace std;

using namespace NGE::InputSystem;
using namespace NGE::InputSystem::Raylib;

RaylibInputHandler::RaylibInputHandler() :
	mouseDeltaInputEvent("Mouse.Delta"),
	mousePositionInputEvent("Mouse.Position"),
	mouseWheelMovementInputEvent("Mouse.WheelMovement")
{
	for (size_t mouse_button_index(static_cast<size_t>(0)); mouse_button_index != mouseButtonInputEvents.size(); mouse_button_index++) {
		string name("Mouse.Button.");
		name += to_string(mouse_button_index);
		mouseButtonInputEvents[mouse_button_index] = InputEvent(std::move(name), false);
	}
	for (size_t gamepad_index(static_cast<size_t>(0)); gamepad_index != gamepadInputEvents.size(); gamepad_index++) {
		gamepadInputEvents[gamepad_index] = RaylibGamepadInputEvents(gamepad_index);
	}
}

vector<InputEvent>& RaylibInputHandler::FetchInputEvents(vector<InputEvent>& result) {
	if (WindowShouldClose()) {
		result.push_back(InputEvent::GetCloseWindowInputEvent());
	}
	int key_code(0);
	while ((key_code = GetKeyPressed())) {
		InputEvent& keyboard_input_event(GetCachedKeyboardInputEvent(key_code));
		if (!keyboard_input_event.IsPressing()) {
			keyboard_input_event = InputEvent(keyboard_input_event, true);
			result.push_back(keyboard_input_event);
		}
	}
	for (auto& keyboard_input_event : keyboardInputEvents) {
		if (IsKeyUp(keyboard_input_event.first) && keyboard_input_event.second.IsPressing()) {
			keyboard_input_event.second = InputEvent(keyboard_input_event.second, false);
			result.push_back(keyboard_input_event.second);
		}
	}
	for (size_t mouse_button_index(0); mouse_button_index != MaximalMouseButtonCount; mouse_button_index++) {
		InputEvent& mouse_button_input_event(mouseButtonInputEvents.at(mouse_button_index));
		if (IsMouseButtonDown(static_cast<int>(mouse_button_index))) {
			if (!mouse_button_input_event.IsPressing()) {
				mouse_button_input_event = InputEvent(mouse_button_input_event, true);
				result.push_back(mouse_button_input_event);
			}
		}
		else if (mouse_button_input_event.IsPressing()) {
			mouse_button_input_event = InputEvent(mouse_button_input_event, false);
			result.push_back(mouse_button_input_event);
		}
	}
	::Vector2 mouse_delta(GetMouseDelta());
	if ((mouse_delta.x != 0.0f) || (mouse_delta.y != 0.0f)) {
		mouseDeltaInputEvent = InputEvent(mouseDeltaInputEvent, NGE::Math::Vector2<float>(mouse_delta.x, mouse_delta.y));
		result.push_back(mouseDeltaInputEvent);
	}
	::Vector2 temp_mouse_position(GetMousePosition());
	NGE::Math::Vector2<float> mouse_position(temp_mouse_position.x, temp_mouse_position.y);
	if (mousePositionInputEvent.GetPressValue2D() != mouse_position) {
		mousePositionInputEvent = InputEvent(mousePositionInputEvent, mouse_position);
		result.push_back(mousePositionInputEvent);
	}
	::Vector2 mouse_wheel_movement(GetMouseWheelMoveV());
	if ((mouse_wheel_movement.x != 0.0f) || (mouse_wheel_movement.y != 0.0f)) {
		mouseWheelMovementInputEvent = InputEvent(mouseWheelMovementInputEvent, NGE::Math::Vector2<float>(mouse_wheel_movement.x, mouse_wheel_movement.y));
		result.push_back(mouseWheelMovementInputEvent);
	}
	for (size_t gamepad_index(0U); gamepad_index != gamepadInputEvents.size(); gamepad_index++) {
		auto& gamepad_input_events = gamepadInputEvents[gamepad_index];
		if (IsGamepadAvailable(static_cast<int>(gamepad_index))) {
			if (!gamepad_input_events.WasGamepadConnected())
			{
				result.push_back(gamepad_input_events.SetGamepadConnectedState(true));
			}
			for (size_t gamepad_button_index(static_cast<size_t>(0)); gamepad_button_index < RaylibGamepadInputEvents::MaximalGamepadButtonCount; gamepad_button_index++) {
				if (IsGamepadButtonDown(static_cast<int>(gamepad_index), gamepad_button_index)) {
					if (!gamepad_input_events.WasButtonDown(gamepad_button_index)) {
						result.push_back(gamepad_input_events.SetButtonDownState(gamepad_button_index, true));
					}
				}
				else if (gamepad_input_events.WasButtonDown(gamepad_button_index)) {
					result.push_back(gamepad_input_events.SetButtonDownState(gamepad_button_index, false));
				}
			}
			for (int gamepad_axis_index(0), gamepad_axis_count(GetGamepadAxisCount(static_cast<int>(gamepad_index)));
				gamepad_axis_index < gamepad_axis_count;
				gamepad_axis_index++) {
				float gamepad_axis_value(GetGamepadAxisMovement(static_cast<int>(gamepad_index), gamepad_axis_index));
				if (gamepad_input_events.GetOldAxisValue(gamepad_axis_index) != gamepad_axis_value) {
					result.push_back(gamepad_input_events.SetAxisValue(gamepad_axis_index, gamepad_axis_value));
				}
			}
		}
		else if (gamepad_input_events.WasGamepadConnected()) {
			for (size_t gamepad_button_index(static_cast<size_t>(0)); gamepad_button_index < RaylibGamepadInputEvents::MaximalGamepadButtonCount; gamepad_button_index++) {
				if (gamepad_input_events.WasButtonDown(gamepad_button_index)) {
					result.push_back(gamepad_input_events.SetButtonDownState(gamepad_button_index, false));
				}
			}
			for (size_t gamepad_axis_index(static_cast<size_t>(0)); gamepad_axis_index < gamepad_input_events.GetUsedAxisCount(); gamepad_axis_index++) {
				if (gamepad_input_events.GetOldAxisValue(gamepad_axis_index) != 0.0f) {
					result.push_back(gamepad_input_events.SetAxisValue(gamepad_axis_index, 0.0f));
				}
			}
			result.push_back(gamepad_input_events.SetGamepadConnectedState(false));
		}
	}
	return result;
}

InputEvent& RaylibInputHandler::GetCachedKeyboardInputEvent(int keyCode) {
	auto it(keyboardInputEvents.find(keyCode));
	if (it != keyboardInputEvents.end()) {
		return it->second;
	}
	else {
		string name("Keyboard.KeyCode.");
		name += to_string(keyCode);
		return keyboardInputEvents.try_emplace(keyCode, std::move(name)).first->second;
	}
}
