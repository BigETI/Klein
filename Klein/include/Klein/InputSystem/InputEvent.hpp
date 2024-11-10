#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <string>

#include "../Exportables/Exportable.hxx"
#include "../Hashing/StringHash.hpp"
#include "../Math/Vector2.hpp"
#include "EInputEventValueType.hpp"

namespace Klein::InputSystem {
	class InputEvent {
	public:

		KLEIN_API InputEvent();
		KLEIN_API InputEvent(const std::string& name);
		KLEIN_API InputEvent(std::string&& name);
		KLEIN_API InputEvent(const std::string& name, bool isPressing);
		KLEIN_API InputEvent(std::string&& name, bool isPressing) noexcept;
		KLEIN_API InputEvent(const std::string& name, float pressValue);
		KLEIN_API InputEvent(std::string&& name, float pressValue) noexcept;
		KLEIN_API InputEvent(const std::string& name, const Klein::Math::Vector2<float>& pressValue2D);
		KLEIN_API InputEvent(std::string&& name, Klein::Math::Vector2<float>&& pressValue2D) noexcept;
		KLEIN_API InputEvent(const Klein::Hashing::StringHash& nameHash);
		KLEIN_API InputEvent(Klein::Hashing::StringHash&& nameHash);
		KLEIN_API InputEvent(const Klein::Hashing::StringHash& nameHash, bool isPressing);
		KLEIN_API InputEvent(Klein::Hashing::StringHash&& nameHash, bool isPressing) noexcept;
		KLEIN_API InputEvent(const Klein::Hashing::StringHash& nameHash, float pressValue);
		KLEIN_API InputEvent(Klein::Hashing::StringHash&& nameHash, float pressValue) noexcept;
		KLEIN_API InputEvent(const Klein::Hashing::StringHash& nameHash, const Klein::Math::Vector2<float>& pressValue2D);
		KLEIN_API InputEvent(Klein::Hashing::StringHash&& nameHash, Klein::Math::Vector2<float>&& pressValue2D) noexcept;
		KLEIN_API InputEvent(const InputEvent& inputEvent);
		KLEIN_API InputEvent(InputEvent&& inputEvent) noexcept;
		KLEIN_API InputEvent(const InputEvent& inputEvent, bool isPressing);
		KLEIN_API InputEvent(InputEvent&& inputEvent, bool isPressing) noexcept;
		KLEIN_API InputEvent(const InputEvent& inputEvent, float pressValue);
		KLEIN_API InputEvent(InputEvent&& inputEvent, float pressValue) noexcept;
		KLEIN_API InputEvent(const InputEvent& inputEvent, const Klein::Math::Vector2<float>& pressValue2D);
		KLEIN_API InputEvent(InputEvent&& inputEvent, Klein::Math::Vector2<float>&& pressValue2D) noexcept;

		KLEIN_API static const InputEvent& GetCloseWindowInputEvent() noexcept;

		KLEIN_API const Klein::Hashing::StringHash& GetNameHash() const noexcept;
		KLEIN_API Klein::Hashing::StringHash& GetNameHash(Klein::Hashing::StringHash& result) const;
		KLEIN_API EInputEventValueType GetInputEventValueType() const noexcept;
		KLEIN_API bool IsPressing() const;
		KLEIN_API float GetPressValue() const;
		KLEIN_API Klein::Math::Vector2<float> GetPressValue2D() const;

		KLEIN_API InputEvent& operator =(const InputEvent& inputEvent);
		KLEIN_API InputEvent& operator =(InputEvent&& inputEvent) noexcept;
		KLEIN_API InputEvent& operator =(bool isPressing);
		KLEIN_API InputEvent& operator =(float pressValue);
		KLEIN_API InputEvent& operator =(const Klein::Math::Vector2<float>& pressValue2D);
		KLEIN_API InputEvent& operator =(Klein::Math::Vector2<float>&& pressValue2D);

	private:

		static const InputEvent closeWindowInputEvent;

		Klein::Hashing::StringHash nameHash;
		EInputEventValueType inputEventValueType;
		std::optional<bool> isPressing;
		std::optional<float> pressValue;
		std::optional<Klein::Math::Vector2<float>> pressValue2D;
	};
}
