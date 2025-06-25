#pragma once

#include <algorithm>
#include <type_traits>
#include <utility>

#include "EAlignment.hpp"
#include "Rectangle.hpp"
#include "Vector2.hpp"

namespace Klein::Math {
	template <typename TComponent>
	struct Border {
		static_assert(
			std::is_same<char, TComponent>::value ||
			std::is_same<short, TComponent>::value ||
			std::is_same<int, TComponent>::value ||
			std::is_same<long, TComponent>::value ||
			std::is_same<long long, TComponent>::value ||
			std::is_same<float, TComponent>::value ||
			std::is_same<double, TComponent>::value ||
			std::is_same<long double, TComponent>::value,
			"The specified border component type must be of a numeric type.");

		TComponent top;
		TComponent bottom;
		TComponent left;
		TComponent right;

		constexpr inline Border() : top(0), bottom(0), left(0), right(0) {
			// ...
		}

		constexpr inline Border(const Border<TComponent>& border) : top(border.top), bottom(border.bottom), left(border.left), right(border.right) {
			// ...
		}

		constexpr inline Border(Border<TComponent>&& border) noexcept :
			top(std::move(border.top)),
			bottom(std::move(border.bottom)),
			left(std::move(border.left)),
			right(std::move(border.right)) {
			// ...
		}

		constexpr inline Border(TComponent top, TComponent bottom, TComponent left, TComponent right) : top(top), bottom(bottom), left(left), right(right) {
			// ...
		}

		template <typename TReturn>
		constexpr inline Border<TReturn> GetConverted() const noexcept {
			return Border<TReturn>(static_cast<TReturn>(top), static_cast<TReturn>(bottom), static_cast<TReturn>(left), static_cast<TReturn>(right));
		}

		template <typename TReturn>
		constexpr inline Border<TReturn>& GetConverted(Border<TReturn>& result) const noexcept {
			return result = GetConverted<TReturn>();
		}

		constexpr inline Border<TComponent>& operator =(const Border<TComponent>& border) {
			top = border.top;
			bottom = border.bottom;
			left = border.left;
			right = border.right;
			return *this;
		}

		constexpr inline Border<TComponent>& operator =(Border<TComponent>&& border) noexcept {
			top = std::move(border.top);
			bottom = std::move(border.bottom);
			left = std::move(border.left);
			right = std::move(border.right);
			return *this;
		}

		constexpr inline bool operator ==(const Border<TComponent>& border) const noexcept {
			return (top == border.top) && (bottom == border.bottom) && (left == border.left) && (right == border.right);
		}

		constexpr inline bool operator !=(const Border<TComponent>& border) const noexcept {
			return (top != border.top) || (bottom != border.bottom) || (left != border.left) || (right != border.right);
		}

		constexpr inline Border<TComponent>& operator +=(const Vector2<TComponent>& offset) noexcept {
			top += offset.y;
			bottom -= offset.y;
			left -= offset.x;
			right += offset.x;
			return *this;
		}

		constexpr inline Border<TComponent> operator +(const Vector2<TComponent>& offset) const noexcept {
			Border<TComponent> ret(*this);
			return ret += offset;
		}

		constexpr inline Border<TComponent>& operator -=(const Vector2<TComponent>& offset) noexcept {
			top -= offset.y;
			bottom += offset.y;
			left += offset.x;
			right -= offset.x;
			return *this;
		}

		constexpr inline Border<TComponent> operator -(const Vector2<TComponent>& offset) const noexcept {
			Border<TComponent> ret(*this);
			return ret -= offset;
		}
	};
}
