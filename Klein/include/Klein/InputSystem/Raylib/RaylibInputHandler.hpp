#pragma once

#include <array>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "../../Exportables/Exportable.hxx"
#include "../../Math/Vector2.hpp"
#include "../IInputHandler.hpp"
#include "../InputEvent.hpp"
#include "RaylibGamepadInputEvents.hpp"

namespace Klein::InputSystem::Raylib {
	class RaylibInputHandler : public Klein::InputSystem::IInputHandler {
	public:

		static constexpr const std::size_t MaximalMouseButtonCount = 7U;
		static constexpr const std::size_t MaximalGamepadCount = 16U;

		KLEIN_API RaylibInputHandler();

		RaylibInputHandler(const RaylibInputHandler&) = delete;
		RaylibInputHandler(RaylibInputHandler&&) = delete;

		KLEIN_API std::vector<Klein::InputSystem::InputEvent>& FetchInputEvents(std::vector<InputEvent>& result) override;
		
		RaylibInputHandler& operator =(const RaylibInputHandler&) = delete;
		RaylibInputHandler& operator =(RaylibInputHandler&&) = delete;

	private:

		std::unordered_map<int, Klein::InputSystem::InputEvent> keyboardInputEvents;
		std::array<Klein::InputSystem::InputEvent, MaximalMouseButtonCount> mouseButtonInputEvents;
		Klein::InputSystem::InputEvent mouseDeltaInputEvent;
		Klein::InputSystem::InputEvent mousePositionInputEvent;
		Klein::InputSystem::InputEvent mouseWheelMovementInputEvent;
		std::array<RaylibGamepadInputEvents, MaximalGamepadCount> gamepadInputEvents;

		Klein::InputSystem::InputEvent& GetCachedKeyboardInputEvent(int keyCode);
	};
}
