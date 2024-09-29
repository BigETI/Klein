#include <cstddef>
#include <string>
#include <utility>

#include <NGE/InputSystem/InputEvent.hpp>
#include <NGE/InputSystem/Raylib/RaylibGamepadInputEvents.hpp>

using namespace std;

using namespace NGE::InputSystem;
using namespace NGE::InputSystem::Raylib;

RaylibGamepadInputEvents::RaylibGamepadInputEvents() : RaylibGamepadInputEvents(static_cast<size_t>(0)) {
	// ...
}

RaylibGamepadInputEvents::RaylibGamepadInputEvents(size_t gamepadIndex) : gamepadIndex(gamepadIndex) {
	string gamepad_name_prefix("Gamepad.");
	gamepad_name_prefix += to_string(gamepadIndex);
	string gamepad_button_prefix(gamepad_name_prefix + ".Button.");
	isConnectedInputEvent = InputEvent(gamepad_name_prefix + ".IsConnected");
	for (size_t gamepad_button_index(static_cast<size_t>(0)); gamepad_button_index != MaximalGamepadButtonCount; gamepad_button_index++) {
		string name(gamepad_button_prefix);
		name += to_string(gamepad_button_index);
		buttonInputEvents[gamepad_button_index] = InputEvent(std::move(name), false);
	}
}

size_t RaylibGamepadInputEvents::GetGamepadIndex() const noexcept {
	return gamepadIndex;
}

bool RaylibGamepadInputEvents::WasGamepadConnected() const noexcept {
	return isConnectedInputEvent.IsPressing();
}

InputEvent RaylibGamepadInputEvents::SetGamepadConnectedState(bool isConnected) {
	return isConnectedInputEvent = isConnected;
}

bool RaylibGamepadInputEvents::WasButtonDown(size_t buttonIndex) const {
	return (buttonIndex < buttonInputEvents.size()) && buttonInputEvents.at(buttonIndex).IsPressing();
}

InputEvent RaylibGamepadInputEvents::SetButtonDownState(size_t buttonIndex, bool isButtonDown) {
	return (buttonIndex < buttonInputEvents.size()) ? (buttonInputEvents[buttonIndex] = isButtonDown) : InputEvent();
}

size_t RaylibGamepadInputEvents::GetUsedAxisCount() const noexcept {
	return axisInputEvents.size();
}

float RaylibGamepadInputEvents::GetOldAxisValue(size_t axisIndex) const noexcept {
	return (axisIndex < axisInputEvents.size()) ? axisInputEvents.at(axisIndex).GetPressValue() : 0.0f;
}

InputEvent RaylibGamepadInputEvents::SetAxisValue(size_t axisIndex, float axisValue) {
	size_t old_axis_count(axisInputEvents.size());
	if (axisIndex >= old_axis_count) {
		string prefix_name("Gamepad." + to_string(gamepadIndex) + ".");
		axisInputEvents.resize(axisIndex + static_cast<size_t>(1));
		for (size_t axis_index(old_axis_count); axis_index != axisInputEvents.size(); axis_index++) {
			axisInputEvents[axis_index] = InputEvent(prefix_name + to_string(axis_index), 0.0f);
		}
	}
	return axisInputEvents[axisIndex] = axisValue;
}
