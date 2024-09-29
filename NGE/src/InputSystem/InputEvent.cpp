#include <algorithm>
#include <numeric>
#include <string>
#include <utility>

#include <NGE/InputSystem/EInputEventValueType.hpp>
#include <NGE/InputSystem/InputEvent.hpp>
#include <NGE/Math/Vector2.hpp>

using namespace std;

using namespace NGE::Hashing;
using namespace NGE::InputSystem;
using namespace NGE::Math;

InputEvent::InputEvent() : inputEventValueType(EInputEventValueType::None) {
	// ...
}

InputEvent::InputEvent(const string& name) : nameHash(name), inputEventValueType(EInputEventValueType::None) {
	// ...
}

InputEvent::InputEvent(string&& name) : nameHash(name), inputEventValueType(EInputEventValueType::None) {
	// ...
}

InputEvent::InputEvent(const string& name, bool isPressing) :
	nameHash(name),
	inputEventValueType(EInputEventValueType::DigitalPress),
	isPressing(isPressing) {
	// ...
}

InputEvent::InputEvent(string&& name, bool isPressing) noexcept :
	nameHash(name),
	inputEventValueType(EInputEventValueType::DigitalPress),
	isPressing(isPressing) {
	// ...
}

InputEvent::InputEvent(const string& name, float pressValue) :
	nameHash(name),
	inputEventValueType(EInputEventValueType::AnalogPress),
	pressValue(pressValue) {
	// ...
}

InputEvent::InputEvent(string&& name, float pressValue) noexcept :
	nameHash(name),
	inputEventValueType(EInputEventValueType::AnalogPress),
	pressValue(pressValue) {
	// ...
}

InputEvent::InputEvent(const string& name, const Vector2<float>& pressValue2D) :
	nameHash(name),
	inputEventValueType(EInputEventValueType::AnalogPress2D),
	pressValue2D(pressValue2D) {
	// ...
}

InputEvent::InputEvent(string&& name, Vector2<float>&& pressValue2D) noexcept :
	nameHash(name),
	inputEventValueType(EInputEventValueType::AnalogPress2D),
	pressValue2D(pressValue2D) {
	// ...
}

InputEvent::InputEvent(const StringHash& nameHash) : nameHash(nameHash), inputEventValueType(EInputEventValueType::None) {
	// ...
}

InputEvent::InputEvent(StringHash&& nameHash) : nameHash(nameHash), inputEventValueType(EInputEventValueType::None) {
	// ...
}

InputEvent::InputEvent(const StringHash& nameHash, bool isPressing) :
	nameHash(nameHash),
	inputEventValueType(EInputEventValueType::DigitalPress),
	isPressing(isPressing) {
	// ...
}

InputEvent::InputEvent(StringHash&& nameHash, bool isPressing) noexcept :
	nameHash(nameHash),
	inputEventValueType(EInputEventValueType::DigitalPress),
	isPressing(isPressing) {
	// ...
}

InputEvent::InputEvent(const StringHash& nameHash, float pressValue) :
	nameHash(nameHash),
	inputEventValueType(EInputEventValueType::AnalogPress),
	pressValue(pressValue) {
	// ...
}

InputEvent::InputEvent(StringHash&& nameHash, float pressValue) noexcept :
	nameHash(nameHash),
	inputEventValueType(EInputEventValueType::AnalogPress),
	pressValue(pressValue) {
	// ...
}

InputEvent::InputEvent(const StringHash& nameHash, const Vector2<float>& pressValue2D) :
	nameHash(nameHash),
	inputEventValueType(EInputEventValueType::AnalogPress2D),
	pressValue2D(pressValue2D) {
	// ...
}

InputEvent::InputEvent(StringHash&& nameHash, Vector2<float>&& pressValue2D) noexcept :
	nameHash(nameHash),
	inputEventValueType(EInputEventValueType::AnalogPress2D),
	pressValue2D(pressValue2D) {
	// ...
}

InputEvent::InputEvent(const InputEvent& inputEvent) :
	nameHash(inputEvent.nameHash),
	inputEventValueType(inputEvent.inputEventValueType),
	isPressing(inputEvent.isPressing),
	pressValue(inputEvent.pressValue),
	pressValue2D(inputEvent.pressValue2D) {
	// ...
}

InputEvent::InputEvent(InputEvent&& inputEvent) noexcept :
	nameHash(std::move(inputEvent.nameHash)),
	inputEventValueType(std::move(inputEvent.inputEventValueType)),
	isPressing(std::move(inputEvent.isPressing)),
	pressValue(std::move(inputEvent.pressValue)),
	pressValue2D(std::move(inputEvent.pressValue2D)) {
	// ...
}

InputEvent::InputEvent(const InputEvent& inputEvent, bool isPressing) :
	nameHash(inputEvent.nameHash),
	inputEventValueType(EInputEventValueType::DigitalPress),
	isPressing(isPressing) {
	// ...
}

InputEvent::InputEvent(InputEvent&& inputEvent, bool isPressing) noexcept :
	nameHash(std::move(inputEvent.nameHash)),
	inputEventValueType(EInputEventValueType::DigitalPress),
	isPressing(isPressing) {
	// ...
}

InputEvent::InputEvent(const InputEvent& inputEvent, float pressValue) :
	nameHash(inputEvent.nameHash),
	inputEventValueType(EInputEventValueType::AnalogPress),
	pressValue(pressValue) {
	// ...
}

InputEvent::InputEvent(InputEvent&& inputEvent, float pressValue) noexcept :
	nameHash(std::move(inputEvent.nameHash)),
	inputEventValueType(EInputEventValueType::AnalogPress),
	pressValue(pressValue) {
	// ...
}

InputEvent::InputEvent(const InputEvent& inputEvent, const NGE::Math::Vector2<float>& pressValue2D) :
	nameHash(inputEvent.nameHash),
	inputEventValueType(EInputEventValueType::AnalogPress2D),
	pressValue2D(pressValue2D) {
	// ...
}

InputEvent::InputEvent(InputEvent&& inputEvent, NGE::Math::Vector2<float>&& pressValue2D) noexcept :
	nameHash(std::move(inputEvent.nameHash)),
	inputEventValueType(EInputEventValueType::AnalogPress2D),
	pressValue2D(std::move(pressValue2D)) {
	// ...
}

const InputEvent& InputEvent::GetCloseWindowInputEvent() noexcept {
	return closeWindowInputEvent;
}

const StringHash& InputEvent::GetNameHash() const noexcept {
	return nameHash;
}

StringHash& InputEvent::GetNameHash(StringHash& result) const {
	return result = nameHash;
}

EInputEventValueType InputEvent::GetInputEventValueType() const noexcept {
	return inputEventValueType;
}

bool InputEvent::IsPressing() const {
	return isPressing.value_or(abs(pressValue.value_or(pressValue2D.value_or(Vector2<float>()).GetLengthSquared<float>())) > numeric_limits<float>::epsilon());
}

float InputEvent::GetPressValue() const {
	return pressValue.value_or(clamp(pressValue2D.value_or(isPressing.value_or(false) ? Vector2<float>() : Vector2<float>(1.0f, 0.0f)).GetLength<float>(), 0.0f, 1.0f));
}

Vector2<float> InputEvent::GetPressValue2D() const {
	return pressValue2D.value_or(Vector2<float>(pressValue.value_or(isPressing.value_or(false) ? 1.0f : 0.0f), 0.0f));
}

InputEvent& InputEvent::operator =(const InputEvent& inputEvent) {
	nameHash = inputEvent.nameHash;
	inputEventValueType = inputEvent.inputEventValueType;
	isPressing = inputEvent.isPressing;
	pressValue = inputEvent.pressValue;
	pressValue2D = inputEvent.pressValue2D;
	return *this;
}

InputEvent& InputEvent::operator =(InputEvent&& inputEvent) noexcept {
	nameHash = std::move(inputEvent.nameHash);
	inputEventValueType = std::move(inputEvent.inputEventValueType);
	isPressing = std::move(inputEvent.isPressing);
	pressValue = std::move(inputEvent.pressValue);
	pressValue2D = std::move(inputEvent.pressValue2D);
	return *this;
}

InputEvent& InputEvent::operator =(bool isPressing) {
	this->isPressing = isPressing;
	pressValue.reset();
	pressValue2D.reset();
	inputEventValueType = EInputEventValueType::DigitalPress;
	return *this;
}

InputEvent& InputEvent::operator =(float pressValue) {
	this->pressValue = pressValue;
	isPressing.reset();
	pressValue2D.reset();
	inputEventValueType = EInputEventValueType::AnalogPress;
	return *this;
}

InputEvent& InputEvent::operator =(const NGE::Math::Vector2<float>& pressValue2D) {
	this->pressValue2D = pressValue2D;
	isPressing.reset();
	pressValue.reset();
	inputEventValueType = EInputEventValueType::AnalogPress2D;
	return *this;
}

InputEvent& InputEvent::operator =(NGE::Math::Vector2<float>&& pressValue2D) {
	this->pressValue2D = pressValue2D;
	isPressing.reset();
	pressValue.reset();
	inputEventValueType = EInputEventValueType::AnalogPress2D;
	return *this;
}

const InputEvent InputEvent::closeWindowInputEvent(InputEvent("System.CloseWindow"));
