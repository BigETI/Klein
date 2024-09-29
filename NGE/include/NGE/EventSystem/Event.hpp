#pragma once

#include <algorithm>
#include <functional>
#include <mutex>
#include <utility>
#include <vector>

#include "ObserverID.hpp"

namespace NGE::EventSystem {

	/// <summary>
	/// A class that enables handling events using the observer pattern
	/// </summary>
	/// <typeparam name="...Ts">Observer argument types</typeparam>
	template <typename... Ts>
	class Event {
	public:

		/// <summary>
		/// Constructs a new event object
		/// </summary>
		Event() : lastRegisteredObserverID(ObserverID::CreateNew()) {
			// ...
		}

		/// <summary>
		/// Constructs a new event object and copies the observers to the newly created event object
		/// </summary>
		/// <param name="e">The event object to copy</param>
		Event(const Event& e) : lastRegisteredObserverID(ObserverID::CreateNew()), observers(e.observers) {
			const std::scoped_lock<std::mutex> observers_scoped_lock(e.observersMutex);
			lastRegisteredObserverID = e.lastRegisteredObserverID;
			observers = e.observers;
		}

		/// <summary>
		/// Constructs a new event object and moves the observers to the newly created event object
		/// </summary>
		/// <param name="e">The event object to be moved</param>
		Event(Event&& e) : lastRegisteredObserverID(ObserverID::CreateNew()), observers(e.observers) {
			const std::scoped_lock<std::mutex> observers_scoped_lock(e.observersMutex);
			lastRegisteredObserverID = std::move(e.lastRegisteredObserverID);
			observers = std::move(e.observers);
		}

		/// <summary>
		/// Adds the specified observer to this event
		/// </summary>
		/// <param name="observer">The observer that observes this event object</param>
		/// <returns>Observer ID</returns>
		ObserverID AddObserver(const std::function<void(Ts...)>& observer) {
			const std::scoped_lock<std::mutex> observers_scoped_lock(observersMutex);
			ObserverID ret(lastRegisteredObserverID);
			observers.push_back({ observer, ret });
			lastRegisteredObserverID = lastRegisteredObserverID.CreateNextObserverID();
			return ret;
		}

		/// <summary>
		/// Adds the specified observer to this event
		/// </summary>
		/// <param name="observer">The observer that observes this event object</param>
		/// <returns></returns>
		ObserverID AddObserver(std::function<void(Ts...)>&& observer) {
			const std::scoped_lock<std::mutex> observers_scoped_lock(observersMutex);
			ObserverID ret(lastRegisteredObserverID);
			observers.push_back({ observer, ret });
			lastRegisteredObserverID = lastRegisteredObserverID.CreateNextObserverID();
			return ret;
		}

		/// <summary>
		/// Removes the specified observer by ID from this event
		/// </summary>
		/// <param name="observerID">Observer ID</param>
		/// <returns>"true" if the specified observer has been successfully removed, otherwise "false"</returns>
		bool RemoveObserverByID(const ObserverID& observerID) {
			bool ret(false);
			if (observerID.IsValid()) {
				const std::scoped_lock<std::mutex> observers_scoped_lock(observersMutex);
				observers.erase(
					std::remove_if(
						observers.begin(),
						observers.end(),
						[&](const auto& currentObserver) {
							bool result = currentObserver.second == observerID;
							ret = ret || result;
							return result;
						}
					),
					observers.end());
			}
			return ret;
		}

		/// <summary>
		/// Clears all observers from this event object
		/// </summary>
		void Clear() {
			const std::scoped_lock<std::mutex> observers_scoped_lock(observersMutex);
			observers.clear();
		}

		/// <summary>
		/// Checks if this event contains the specified observer ID
		/// </summary>
		/// <param name="observerID">The observer ID that observes this event object</param>
		/// <returns>"true" if observer ID is contained in this event object, otherwise "false"</returns>
		bool IsObserverIDContained(const ObserverID& observerID) const noexcept {
			bool ret(false);
			if (observerID.IsValid()) {
				const std::scoped_lock<std::mutex> observers_scoped_lock(observersMutex);
				for (const std::pair<std::function<void(Ts...)>, ObserverID>& observer : observers) {
					if (observer.second == observerID) {
						ret = true;
						break;
					}
				}
			}
			return ret;
		}

		/// <summary>
		/// Checks if this event object has no observers attached to it
		/// </summary>
		/// <returns>"true" if this event object has no observers attached to it, otherwise "false"</returns>
		bool IsEmpty() const noexcept {
			const std::scoped_lock<std::mutex> observers_scoped_lock(observersMutex);
			return observers.empty();
		}

		/// <summary>
		/// Invokes this event and notifies all observers that this event has been invoked
		/// </summary>
		/// <param name="...arguments">Listener arguments</param>
		void operator()(Ts... arguments) const {
			observersMutex.lock();
			std::vector<std::pair<std::function<void(Ts...)>, ObserverID>> current_observers(observers);
			observersMutex.unlock();
			for (const auto& observer : current_observers) {
				observer.first(arguments...);
			}
		}

		/// <summary>
		/// Assigns the contents of the specified event object to this event object
		/// </summary>
		/// <param name="e">The event object to copy from</param>
		/// <returns>Itself</returns>
		Event& operator=(const Event& e) {
			const std::scoped_lock<std::mutex> observers_scoped_lock(observersMutex, e.observersMutex);
			observers = e.observers;
			return *this;
		}

		/// <summary>
		/// Moves the contents of the specified event object to this event object
		/// </summary>
		/// <param name="e">The event object to move</param>
		/// <returns>Itself</returns>
		Event& operator=(Event&& e) noexcept {
			const std::scoped_lock<std::mutex> observers_scoped_lock(observersMutex, e.observersMutex);
			observers = std::move(e.observers);
			return *this;
		}

		/// <summary>
		/// Adds the specified observer to this event
		/// </summary>
		/// <param name="observer">The observer to add</param>
		/// <returns>Itself</returns>
		Event& operator+=(const std::function<void(Ts...)>& observer) {
			AddObserver(observer);
			return *this;
		}

		/// <summary>
		/// Adds and moves the specified observer to this event
		/// </summary>
		/// <param name="observer">The observer to add and move</param>
		/// <returns>Itself</returns>
		Event& operator+=(std::function<void(Ts...)>&& observer) {
			AddObserver(observer);
			return *this;
		}

		/// <summary>
		/// Removes the specified observer by ID from this event
		/// </summary>
		/// <param name="observerID">The observer ID that observes this event object</param>
		/// <returns>Itself</returns>
		Event& operator-=(const ObserverID& observerID) {
			RemoveObserverByID(observerID);
			return *this;
		}

	private:

		/// <summary>
		/// Registered observers
		/// </summary>
		std::vector<std::pair<std::function<void(Ts...)>, ObserverID>> observers;

		/// <summary>
		/// The mutex used to keep the state of the observers valid
		/// </summary>
		mutable std::mutex observersMutex;

		/// <summary>
		/// Last registered observer ID
		/// </summary>
		ObserverID lastRegisteredObserverID;
	};
}
