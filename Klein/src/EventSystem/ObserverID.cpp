#include <Klein/EventSystem/ObserverID.hpp>

using namespace Klein::EventSystem;

ObserverID::ObserverID() : value(InvalidValue) {
	// ...
}

ObserverID::ObserverID(const ObserverID& observerID) : value(observerID.value) {
	// ...
}

ObserverID::ObserverID(ObserverID&& observerID) noexcept : value(observerID.value) {
	// ...
}

ObserverID::ObserverID(unsigned int value) : value(value) {
	// ...
}

ObserverID ObserverID::CreateNew() {
	return ObserverID(0U);
}
bool ObserverID::IsValid() const noexcept {
	return value != InvalidValue;
}

ObserverID ObserverID::CreateNextObserverID() const {
	ObserverID ret(*this);
	++ret.value;
	if (ret.value == InvalidValue) {
		ret.value = 0U;
	}
	return ret;
}

ObserverID& ObserverID::operator =(const ObserverID& observerID) {
	value = observerID.value;
	return *this;
}

ObserverID& ObserverID::operator =(ObserverID&& observerID) noexcept {
	value = observerID.value;
	return *this;
}

bool ObserverID::operator ==(const ObserverID& observerID) const noexcept {
	return value == observerID.value;
}

bool ObserverID::operator !=(const ObserverID& observerID) const noexcept {
	return value != observerID.value;
}
