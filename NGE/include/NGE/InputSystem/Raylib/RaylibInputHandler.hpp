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

namespace NGE::InputSystem::Raylib {
	class RaylibInputHandler : public NGE::InputSystem::IInputHandler {
	public:

		static constexpr const std::size_t MaximalMouseButtonCount = 7U;
		static constexpr const std::size_t MaximalGamepadCount = 16U;

		NGE_API RaylibInputHandler();

		RaylibInputHandler(const RaylibInputHandler&) = delete;
		RaylibInputHandler(RaylibInputHandler&&) = delete;

		NGE_API std::vector<NGE::InputSystem::InputEvent>& FetchInputEvents(std::vector<InputEvent>& result) override;
		
		RaylibInputHandler& operator =(const RaylibInputHandler&) = delete;
		RaylibInputHandler& operator =(RaylibInputHandler&&) = delete;

	private:

		std::unordered_map<int, NGE::InputSystem::InputEvent> keyboardInputEvents;
		std::array<NGE::InputSystem::InputEvent, MaximalMouseButtonCount> mouseButtonInputEvents;
		NGE::InputSystem::InputEvent mouseDeltaInputEvent;
		NGE::InputSystem::InputEvent mousePositionInputEvent;
		NGE::InputSystem::InputEvent mouseWheelMovementInputEvent;
		std::array<RaylibGamepadInputEvents, MaximalGamepadCount> gamepadInputEvents;

		NGE::InputSystem::InputEvent& GetCachedKeyboardInputEvent(int keyCode);
	};
}
