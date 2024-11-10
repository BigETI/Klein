#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "../../Exportables/Exportable.hxx"
#include "../InputEvent.hpp"

namespace Klein::InputSystem::Raylib {
	class RaylibGamepadInputEvents {
	public:

		static constexpr const std::size_t MaximalGamepadButtonCount = 18U;

		KLEIN_API RaylibGamepadInputEvents();
		KLEIN_API RaylibGamepadInputEvents(std::size_t gamepadIndex);

		KLEIN_API std::size_t GetGamepadIndex() const noexcept;
		KLEIN_API bool WasGamepadConnected() const noexcept;
		KLEIN_API Klein::InputSystem::InputEvent SetGamepadConnectedState(bool isConnected);
		KLEIN_API bool WasButtonDown(std::size_t buttonIndex) const;
		KLEIN_API Klein::InputSystem::InputEvent SetButtonDownState(std::size_t buttonIndex, bool isButtonDown);
		KLEIN_API std::size_t GetUsedAxisCount() const noexcept;
		KLEIN_API float GetOldAxisValue(std::size_t axisIndex) const noexcept;
		KLEIN_API Klein::InputSystem::InputEvent SetAxisValue(std::size_t axisIndex, float axisValue);

	private:

		std::size_t gamepadIndex;
		Klein::InputSystem::InputEvent isConnectedInputEvent;
		std::array<InputEvent, MaximalGamepadButtonCount> buttonInputEvents;
		std::vector<InputEvent> axisInputEvents;
	};
}
