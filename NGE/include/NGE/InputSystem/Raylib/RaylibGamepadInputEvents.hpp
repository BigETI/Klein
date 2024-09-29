#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "../../Exportables/Exportable.hxx"
#include "../InputEvent.hpp"

namespace NGE::InputSystem::Raylib {
	class RaylibGamepadInputEvents {
	public:

		static constexpr const std::size_t MaximalGamepadButtonCount = 18U;

		NGE_API RaylibGamepadInputEvents();
		NGE_API RaylibGamepadInputEvents(std::size_t gamepadIndex);

		NGE_API std::size_t GetGamepadIndex() const noexcept;
		NGE_API bool WasGamepadConnected() const noexcept;
		NGE_API NGE::InputSystem::InputEvent SetGamepadConnectedState(bool isConnected);
		NGE_API bool WasButtonDown(std::size_t buttonIndex) const;
		NGE_API NGE::InputSystem::InputEvent SetButtonDownState(std::size_t buttonIndex, bool isButtonDown);
		NGE_API std::size_t GetUsedAxisCount() const noexcept;
		NGE_API float GetOldAxisValue(std::size_t axisIndex) const noexcept;
		NGE_API NGE::InputSystem::InputEvent SetAxisValue(std::size_t axisIndex, float axisValue);

	private:

		std::size_t gamepadIndex;
		NGE::InputSystem::InputEvent isConnectedInputEvent;
		std::array<InputEvent, MaximalGamepadButtonCount> buttonInputEvents;
		std::vector<InputEvent> axisInputEvents;
	};
}
