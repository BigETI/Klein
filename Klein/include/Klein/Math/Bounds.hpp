#pragma once

#include <algorithm>
#include <type_traits>
#include <utility>

#include "EAlignment.hpp"
#include "Border.hpp"
#include "Rectangle.hpp"
#include "Vector2.hpp"

namespace Klein::Math {

	template <typename TComponent>
	struct Border;

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

		constexpr inline bool IsIntersecting(const Bounds<TComponent>& bounds) const noexcept {
			return
				((left >= bounds.left) || (right >= bounds.left)) &&
				((left <= bounds.right) || (right <= bounds.right)) &&
				((top >= bounds.top) || (bottom >= bounds.top)) &&
				((top <= bounds.bottom) || (bottom <= bounds.bottom));
		}

		constexpr inline Vector2<TComponent> GetClampedPosition(const Vector2<TComponent>& position) const noexcept {
			return Vector2<TComponent>(std::clamp(position.x, left, right), std::clamp(position.y, bottom, top));
		}

		constexpr inline Bounds<TComponent> GetCorrected() const noexcept {
			return Bounds<TComponent>(
				std::max(top, bottom),
				std::min(top, bottom),
				std::min(left, right),
				std::max(left, right)
			);
		}

		constexpr inline Bounds<TComponent>& GetCorrected(Bounds<TComponent>& result) const noexcept {
			return result = GetCorrected();
		}

		template <typename TReturn>
		constexpr inline Bounds<TReturn> GetConverted() const noexcept {
			return Bounds<TReturn>(static_cast<TReturn>(top), static_cast<TReturn>(bottom), static_cast<TReturn>(left), static_cast<TReturn>(right));
		}

		template <typename TReturn>
		constexpr inline Bounds<TReturn>& GetConverted(Bounds<TReturn>& result) const noexcept {
			return result = GetConverted<TReturn>();
		}

		constexpr inline Rectangle<TComponent> GetRectangle(EAlignment alignment) const noexcept {
			switch (alignment) {
			case EAlignment::TopLeft:
				return Rectangle<TComponent>(
					Vector2<TComponent>(left, top),
					Vector2<TComponent>(right - left, top - bottom)
				);
				break;
			case EAlignment::TopRight:
				return Rectangle<TComponent>(
					Vector2<TComponent>(right, top),
					Vector2<TComponent>(right - left, top - bottom)
				);
				break;
			case EAlignment::BottomLeft:
				return Rectangle<TComponent>(
					Vector2<TComponent>(left, bottom),
					Vector2<TComponent>(right - left, top - bottom)
				);
				break;
			case EAlignment::BottomRight:
				return Rectangle<TComponent>(
					Vector2<TComponent>(right, bottom),
					Vector2<TComponent>(right - left, top - bottom)
				);
				break;
			case EAlignment::Center:
				return Rectangle<TComponent>(
					Vector2<TComponent>((left + right) / static_cast<TComponent>(2), (bottom + top) / static_cast<TComponent>(2)),
					Vector2<TComponent>(right - left, top - bottom)
				);
				break;
			}
			return Rectangle<TComponent>();
		}

		constexpr inline Rectangle<TComponent>& GetRectangle(EAlignment alignment, Rectangle<TComponent>& result) const noexcept {
			return result = GetRectangle(alignment);
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

		constexpr inline Bounds<TComponent>& operator +=(const Border<TComponent>& border) noexcept {
			top += border.top;
			bottom -= border.bottom;
			left -= border.left;
			right += border.right;
			return *this;
		}

		constexpr inline Bounds<TComponent> operator +(const Border<TComponent>& border) const noexcept {
			Bounds<TComponent> ret(*this);
			return ret += border;
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

		constexpr inline Bounds<TComponent>& operator -=(const Border<TComponent>& border) noexcept {
			top -= border.top;
			bottom += border.bottom;
			left += border.left;
			right -= border.right;
			return *this;
		}

		constexpr inline Bounds<TComponent> operator -(const Border<TComponent>& border) const noexcept {
			Bounds<TComponent> ret(*this);
			return ret -= border;
		}
	};
}
