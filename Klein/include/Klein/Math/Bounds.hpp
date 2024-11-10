#pragma once

#include <cmath>
#include <type_traits>
#include <utility>

#include "Rectangle.hpp"
#include "Vector2.hpp"

namespace Klein::Math {

	template <typename TComponent>
	struct Rectangle;

	template <typename TComponent>
	struct Bounds {
		static_assert(
			std::is_same<char, TComponent>::value ||
			std::is_same<short, TComponent>::value ||
			std::is_same<int, TComponent>::value ||
			std::is_same<long, TComponent>::value ||
			std::is_same<long long, TComponent>::value ||
			std::is_same<float, TComponent>::value ||
			std::is_same<double, TComponent>::value ||
			std::is_same<long double, TComponent>::value,
			"The specified bounds component type must be of a numeric type.");

		TComponent top;
		TComponent bottom;
		TComponent left;
		TComponent right;

		constexpr inline Bounds() : top(0), bottom(0), left(0), right(0) {
			// ...
		}

		constexpr inline Bounds(const Bounds<TComponent>& bounds) : top(bounds.top), bottom(bounds.bottom), left(bounds.left), right(bounds.right) {
			// ...
		}

		constexpr inline Bounds(Bounds<TComponent>&& bounds) noexcept :
			top(std::move(bounds.top)),
			bottom(std::move(bounds.bottom)),
			left(std::move(bounds.left)),
			right(std::move(bounds.right)) {
			// ...
		}

		constexpr inline Bounds(TComponent top, TComponent bottom, TComponent left, TComponent right) : top(top), bottom(bottom), left(left), right(right) {
			// ...
		}

		constexpr inline bool IsContained(const Vector2<TComponent>& position) const noexcept {
			return (position.y <= top) && (position.y >= bottom) && (position.x >= left) && (position.x <= right);
		}

		constexpr inline Bounds<TComponent> GetCorrected() const noexcept {
			return Rectangle<TComponent>(
				std::min(top, bottom),
				std::max(top, bottom),
				std::min(left, right),
				std::max(left, right)
			);
		}
		
		constexpr inline Bounds<TComponent>& GetCorrected(Bounds<TComponent>& result) const noexcept {
			return result = Rectangle<TComponent>(std::min(top, bottom), std::max(top, bottom), std::min(left, right), std::max(left, right));
		}

		template <typename TReturn>
		constexpr inline Bounds<TReturn> GetConverted() const noexcept {
			return Bounds<TReturn>(static_cast<TReturn>(top), static_cast<TReturn>(bottom), static_cast<TReturn>(left), static_cast<TReturn>(right));
		}

		template <typename TReturn>
		constexpr inline Bounds<TReturn>& GetConverted(Bounds<TReturn>& result) const noexcept {
			return result = GetConverted<TReturn>();
		}

		constexpr inline Rectangle<TComponent> GetRectangle() const noexcept {
			return Rectangle<TComponent>(
				Vector2<TComponent>(left, top),
				Vector2<TComponent>(right - left, bottom - top)
			);
		}

		constexpr inline Rectangle<TComponent>& GetRectangle(Rectangle<TComponent>& result) const noexcept {
			return result = GetRectangle();
		}

		constexpr inline Bounds<TComponent>& operator =(const Bounds<TComponent>& bounds) {
			top = bounds.top;
			bottom = bounds.bottom;
			left = bounds.left;
			right = bounds.right;
			return *this;
		}

		constexpr inline Bounds<TComponent>& operator =(Bounds<TComponent>&& bounds) noexcept {
			top = std::move(bounds.top);
			bottom = std::move(bounds.bottom);
			left = std::move(bounds.left);
			right = std::move(bounds.right);
			return *this;
		}

		constexpr inline bool operator ==(const Bounds<TComponent>& bounds) const noexcept {
			return (top == bounds.top) && (bottom == bounds.bottom) && (left == bounds.left) && (right == bounds.right);
		}

		constexpr inline bool operator !=(const Bounds<TComponent>& bounds) const noexcept {
			return (top != bounds.top) || (bottom != bounds.bottom) || (left != bounds.left) || (right != bounds.right);
		}

		constexpr inline Bounds<TComponent>& operator +=(const Vector2<TComponent>& offset) noexcept {
			top += offset.y;
			bottom += offset.y;
			left += offset.x;
			right += offset.x;
			return *this;
		}

		constexpr inline Bounds<TComponent> operator +(const Vector2<TComponent>& offset) const noexcept {
			Bounds<TComponent> ret(*this);
			return ret += offset;
		}
	
		constexpr inline Bounds<TComponent>& operator -=(const Vector2<TComponent>& offset) noexcept {
			top -= offset.y;
			bottom -= offset.y;
			left -= offset.x;
			right -= offset.x;
			return *this;
		}

		constexpr inline Bounds<TComponent> operator -(const Vector2<TComponent>& offset) const noexcept {
			Bounds<TComponent> ret(*this);
			return ret -= offset;
		}
	};
}
