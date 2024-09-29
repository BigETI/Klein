#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <string>

#include "../Exportables/Exportable.hxx"
#include "../Hashing/StringHash.hpp"
#include "../Math/Vector2.hpp"
#include "EInputEventValueType.hpp"

namespace NGE::InputSystem {
	class InputEvent {
	public:

		NGE_API InputEvent();
		NGE_API InputEvent(const std::string& name);
		NGE_API InputEvent(std::string&& name);
		NGE_API InputEvent(const std::string& name, bool isPressing);
		NGE_API InputEvent(std::string&& name, bool isPressing) noexcept;
		NGE_API InputEvent(const std::string& name, float pressValue);
		NGE_API InputEvent(std::string&& name, float pressValue) noexcept;
		NGE_API InputEvent(const std::string& name, const NGE::Math::Vector2<float>& pressValue2D);
		NGE_API InputEvent(std::string&& name, NGE::Math::Vector2<float>&& pressValue2D) noexcept;
		NGE_API InputEvent(const NGE::Hashing::StringHash& nameHash);
		NGE_API InputEvent(NGE::Hashing::StringHash&& nameHash);
		NGE_API InputEvent(const NGE::Hashing::StringHash& nameHash, bool isPressing);
		NGE_API InputEvent(NGE::Hashing::StringHash&& nameHash, bool isPressing) noexcept;
		NGE_API InputEvent(const NGE::Hashing::StringHash& nameHash, float pressValue);
		NGE_API InputEvent(NGE::Hashing::StringHash&& nameHash, float pressValue) noexcept;
		NGE_API InputEvent(const NGE::Hashing::StringHash& nameHash, const NGE::Math::Vector2<float>& pressValue2D);
		NGE_API InputEvent(NGE::Hashing::StringHash&& nameHash, NGE::Math::Vector2<float>&& pressValue2D) noexcept;
		NGE_API InputEvent(const InputEvent& inputEvent);
		NGE_API InputEvent(InputEvent&& inputEvent) noexcept;
		NGE_API InputEvent(const InputEvent& inputEvent, bool isPressing);
		NGE_API InputEvent(InputEvent&& inputEvent, bool isPressing) noexcept;
		NGE_API InputEvent(const InputEvent& inputEvent, float pressValue);
		NGE_API InputEvent(InputEvent&& inputEvent, float pressValue) noexcept;
		NGE_API InputEvent(const InputEvent& inputEvent, const NGE::Math::Vector2<float>& pressValue2D);
		NGE_API InputEvent(InputEvent&& inputEvent, NGE::Math::Vector2<float>&& pressValue2D) noexcept;

		NGE_API static const InputEvent& GetCloseWindowInputEvent() noexcept;

		NGE_API const NGE::Hashing::StringHash& GetNameHash() const noexcept;
		NGE_API NGE::Hashing::StringHash& GetNameHash(NGE::Hashing::StringHash& result) const;
		NGE_API EInputEventValueType GetInputEventValueType() const noexcept;
		NGE_API bool IsPressing() const;
		NGE_API float GetPressValue() const;
		NGE_API NGE::Math::Vector2<float> GetPressValue2D() const;

		NGE_API InputEvent& operator =(const InputEvent& inputEvent);
		NGE_API InputEvent& operator =(InputEvent&& inputEvent) noexcept;
		NGE_API InputEvent& operator =(bool isPressing);
		NGE_API InputEvent& operator =(float pressValue);
		NGE_API InputEvent& operator =(const NGE::Math::Vector2<float>& pressValue2D);
		NGE_API InputEvent& operator =(NGE::Math::Vector2<float>&& pressValue2D);

	private:

		static const InputEvent closeWindowInputEvent;

		NGE::Hashing::StringHash nameHash;
		EInputEventValueType inputEventValueType;
		std::optional<bool> isPressing;
		std::optional<float> pressValue;
		std::optional<NGE::Math::Vector2<float>> pressValue2D;
	};
}
