#pragma once

#include <functional>
#include <utility>

namespace Klein::EventSystem {

	/// <summary>
	/// A class that describes an observer ID used to for example identify observers within events
	/// </summary>
	class ObserverID {
	public:

		/// <summary>
		/// Invalid observer ID value
		/// </summary>
		static constexpr unsigned int InvalidValue = ~0U;

		/// <summary>
		/// Invalid observer ID
		/// </summary>
		static const ObserverID Invalid;

		/// <summary>
		/// Constructs a new observer ID
		/// </summary>
		ObserverID();

		/// <summary>
		/// Constructs a new observer ID and copies the contents of the specified observer ID into this oberver ID
		/// </summary>
		/// <param name="observerID">Observer ID to copy from</param>
		ObserverID(const ObserverID& observerID);

		/// <summary>
		/// Constructs a new observer ID and moves the contents of the specified observer ID into this oberver ID
		/// </summary>
		/// <param name="observerID">Observer ID to move</param>
		ObserverID(ObserverID&& observerID) noexcept;

		/// <summary>
		/// Creates a new observer ID
		/// </summary>
		/// <returns>New observer ID</returns>
		static ObserverID CreateNew();

		/// <summary>
		/// Checks if this observer ID is valid
		/// </summary>
		/// <returns>"true" if observer ID is valid, otherwise "false"</returns>
		bool IsValid() const noexcept;

		/// <summary>
		/// Creates the next observer ID from this observer
		/// </summary>
		/// <returns>Next observer ID</returns>
		ObserverID CreateNextObserverID() const;

		/// <summary>
		/// Assigns the specified observer ID to this observer ID
		/// </summary>
		/// <param name="observerID">Observer ID to assign from</param>
		/// <returns>Itself</returns>
		ObserverID& operator =(const ObserverID& observerID);

		/// <summary>
		/// Moves the specified observer ID to this observer ID
		/// </summary>
		/// <param name="observerID">Observer ID to move</param>
		/// <returns>Itself</returns>
		ObserverID& operator =(ObserverID&& observerID) noexcept;

		/// <summary>
		/// Checks if this observer ID and the specified observer IDs are equal
		/// </summary>
		/// <param name="observerID">Observer ID to compare with</param>
		/// <returns>"true" if both observer IDs are equal, otherwise "false"</returns>
		bool operator ==(const ObserverID& observerID) const noexcept;

		/// <summary>
		/// Checks if this observer ID and the specified observer IDs are not equal
		/// </summary>
		/// <param name="observerID">Observer ID to compare with</param>
		/// <returns>"true" if both observer IDs are not equal, otherwise "false"</returns>
		bool operator !=(const ObserverID& observerID) const noexcept;

	private:

		/// <summary>
		/// The value of this observer ID
		/// </summary>
		unsigned int value;

		/// <summary>
		/// Constructs a new observer ID with the specified observer ID value
		/// </summary>
		/// <param name="value">Observer ID value</param>
		ObserverID(unsigned int value);
	};
}
