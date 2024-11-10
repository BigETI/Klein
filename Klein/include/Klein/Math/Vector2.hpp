#pragma once

#include <cmath>
#include <type_traits>
#include <utility>

namespace Klein::Math {

	/// <summary>
	/// A structure that describes a 2D vector
	/// </summary>
	/// <typeparam name="TComponent">Component type</typeparam>
	template <typename TComponent>
	struct Vector2 {
		static_assert(
			std::is_same<char, TComponent>::value ||
			std::is_same<unsigned char, TComponent>::value ||
			std::is_same<short, TComponent>::value ||
			std::is_same<unsigned short, TComponent>::value ||
			std::is_same<int, TComponent>::value ||
			std::is_same<unsigned int, TComponent>::value ||
			std::is_same<long, TComponent>::value ||
			std::is_same<unsigned long, TComponent>::value ||
			std::is_same<long long, TComponent>::value ||
			std::is_same<unsigned long long, TComponent>::value ||
			std::is_same<float, TComponent>::value ||
			std::is_same<double, TComponent>::value ||
			std::is_same<long double, TComponent>::value,
			"The specified vector component type must be of a numeric type.");

		/// <summary>
		/// The X component of this 2D vector
		/// </summary>
		TComponent x;

		/// <summary>
		/// The Y component of this 2D vector
		/// </summary>
		TComponent y;

		/// <summary>
		/// Constructs a new 2D vector
		/// </summary>
		constexpr inline Vector2() : x(0), y(0) {
			// ...
		}

		/// <summary>
		/// Constructs a new vector and copies the specified 2D vector into this 2D vector
		/// </summary>
		/// <param name="vector">Vector to be copied from</param>
		constexpr inline Vector2(const Vector2<TComponent>& vector) : x(vector.x), y(vector.y) {
			// ...
		}

		/// <summary>
		/// Constructs a new vector and moves the contents of the specified 2D vector to this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to move</param>
		constexpr inline Vector2(Vector2<TComponent>&& vector) noexcept : x(std::move(vector.x)), y(std::move(vector.y)) {
			// ...
		}

		/// <summary>
		/// Constructs a new 2D vector with the specified components
		/// </summary>
		/// <param name="x">The X component</param>
		/// <param name="y">The Y component</param>
		constexpr inline Vector2(TComponent x, TComponent y) : x(x), y(y) {
			// ...
		}

		/// <summary>
		/// Gets the length squared of this 2D vector
		/// </summary>
		/// <typeparam name="TReturn">Return type</typeparam>
		/// <returns>The length squared of this vector</returns>
		template <typename TReturn = double>
		constexpr inline TReturn GetLengthSquared() const noexcept {
			return static_cast<TReturn>((x * x) + (y * y));
		}

		/// <summary>
		/// Gets the length of this 2D vector
		/// </summary>
		/// <typeparam name="TReturn">Return type</typeparam>
		/// <returns>The length of this vector</returns>
		template <typename TReturn = double>
		constexpr inline TReturn GetLength() const noexcept {
			return std::sqrt(GetLengthSquared<TReturn>());
		}
		
		/// <summary>
		/// Gets the normalized vector of this 2D vector
		/// </summary>
		/// <typeparam name="TReturn">Return type</typeparam>
		/// <returns></returns>
		template <typename TReturn = double>
		constexpr inline Vector2<TReturn> GetNormalized() const noexcept {
			return GetConverted<TReturn>() / GetLength<TReturn>();
		}

		/// <summary>
		/// Gets this 2D vector with the components converted to the specified type
		/// </summary>
		/// <typeparam name="TReturn">Return type</typeparam>
		/// <returns>This 2D vector with the components converted to the specified type</returns>
		template <typename TReturn>
		constexpr inline Vector2<TReturn> GetConverted() const noexcept {
			return Vector2<TReturn>(static_cast<TReturn>(x), static_cast<TReturn>(y));
		}

		/// <summary>
		/// Gets this 2D vector with the components converted to the specified type
		/// </summary>
		/// <typeparam name="TReturn">Return type</typeparam>
		/// <param name="result">This 2D vector with the components converted to the specified type</param>
		/// <returns>This 2D vector with the components converted to the specified type</returns>
		template <typename TReturn>
		constexpr inline Vector2<TReturn>& GetConverted(Vector2<TReturn>& result) const noexcept {
			return result = Vector2<TReturn>(static_cast<TReturn>(x), static_cast<TReturn>(y));
		}

		/// <summary>
		/// Assigns the specified 2D vector to this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to assign from</param>
		/// <returns>Itself</returns>
		constexpr inline Vector2<TComponent>& operator =(const Vector2<TComponent>& vector) {
			x = vector.x;
			y = vector.y;
			return *this;
		}

		/// <summary>
		/// Moves the contents of the specified 2D vector to this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to move</param>
		/// <returns>Itself</returns>
		constexpr inline Vector2<TComponent>& operator =(Vector2<TComponent>&& vector) noexcept {
			x = std::move(vector.x);
			y = std::move(vector.y);
			return *this;
		}

		/// <summary>
		/// Checks if this 2D vector is equal to the specified 2D vector
		/// </summary>
		/// <param name="vector">2D vector to compare with</param>
		/// <returns>"true" if both 2D vectors are equal, otherwise "false"</returns>
		constexpr inline bool operator ==(const Vector2<TComponent>& vector) const noexcept {
			return (x == vector.x) && (y == vector.y);
		}

		/// <summary>
		/// Checks if this 2D vector is not equal to the specified 2D vector
		/// </summary>
		/// <param name="vector">2D vector to compare with</param>
		/// <returns>"true" if both 2D vectors are not equal, otherwise "false"</returns>
		constexpr inline bool operator !=(const Vector2<TComponent>& vector) const noexcept {
			return (x != vector.x) || (y != vector.y);
		}

		/// <summary>
		/// Adds the specified 2D vector to this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to add from</param>
		/// <returns>Itself</returns>
		constexpr inline Vector2<TComponent>& operator +=(const Vector2<TComponent>& vector) noexcept {
			x += vector.x;
			y += vector.y;
			return *this;
		}

		/// <summary>
		/// Subtracts the specified 2D vector from this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to subtract with</param>
		/// <returns>Itself</returns>
		constexpr inline Vector2& operator -=(const Vector2& vector) noexcept {
			x -= vector.x;
			y -= vector.y;
			return *this;
		}

		/// <summary>
		/// Multiplies the specified scalar to this 2D vector
		/// </summary>
		/// <param name="value">Scalar to multiply from</param>
		/// <returns>Itself</returns>
		constexpr inline Vector2<TComponent>& operator *=(TComponent value) noexcept {
			x *= value;
			y *= value;
			return *this;
		}

		/// <summary>
		/// Multiplies the specified 2D vector with this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to multiply with</param>
		/// <returns>Itself</returns>
		constexpr inline Vector2<TComponent>& operator *=(const Vector2<TComponent>& vector) noexcept {
			x *= vector.x;
			y *= vector.y;
			return *this;
		}

		/// <summary>
		/// Divides the specified scalar with this 2D vector
		/// </summary>
		/// <param name="value">Scalar to divide with</param>
		/// <returns>Itself</returns>
		constexpr inline Vector2<TComponent>& operator /=(TComponent value) noexcept {
			x /= value;
			y /= value;
			return *this;
		}

		/// <summary>
		/// Divides the specified 2D vector with this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to divide with</param>
		/// <returns>Itself</returns>
		constexpr inline Vector2<TComponent>& operator /=(const Vector2<TComponent>& vector) noexcept {
			x /= vector.x;
			y /= vector.y;
			return *this;
		}

		/// <summary>
		/// Adds the specified 2D vector to this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to add from</param>
		/// <returns>Added 2D vector</returns>
		constexpr inline Vector2<TComponent> operator +(const Vector2<TComponent>& vector) const {
			return Vector2<TComponent>(*this) += vector;
		}

		/// <summary>
		/// Subtracts the specified 2D vector from this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to subtract from</param>
		/// <returns>Subtracted 2D vector</returns>
		constexpr inline Vector2<TComponent> operator -(const Vector2<TComponent>& vector) const {
			return Vector2<TComponent>(*this) -= vector;
		}

		/// <summary>
		/// Multiplies the specified scalar with this 2D vector
		/// </summary>
		/// <param name="value">Scalar to multiply with</param>
		/// <returns>Multiplied 2D vector</returns>
		constexpr inline Vector2<TComponent> operator *(TComponent value) const {
			return Vector2<TComponent>(*this) *= value;
		}

		/// <summary>
		/// Multiplies the specified 2D vector with this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to multiply with</param>
		/// <returns>Multiplied 2D vector</returns>
		constexpr inline Vector2<TComponent> operator *(const Vector2<TComponent>& vector) const {
			return Vector2<TComponent>(*this) *= vector;
		}

		/// <summary>
		/// Divides the specified scalar with this 2D vector
		/// </summary>
		/// <param name="value">Scalar to divide with</param>
		/// <returns>Divided 2D vector</returns>
		constexpr inline Vector2<TComponent> operator /(TComponent value) const {
			return Vector2<TComponent>(*this) /= value;
		}

		/// <summary>
		/// Divides the specified 2D vector with this 2D vector
		/// </summary>
		/// <param name="vector">2D vector to divide with</param>
		/// <returns>Divided 2D vector</returns>
		constexpr inline Vector2<TComponent> operator /(const Vector2& vector) const {
			return Vector2<TComponent>(*this) /= vector;
		}
	};
}
