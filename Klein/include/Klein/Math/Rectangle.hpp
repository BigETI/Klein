#pragma once

#include <algorithm>
#include <type_traits>
#include <utility>

#include "Bounds.hpp"
#include "EAlignment.hpp"
#include "Vector2.hpp"

namespace Klein::Math {

	template <typename TComponent>
	struct Bounds;

	template <typename TComponent>
	struct Rectangle {
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

		Vector2<TComponent> position;
		Vector2<TComponent> size;

		constexpr inline Rectangle() noexcept {
			// ...
		}

		constexpr inline Rectangle(const Rectangle& rectangle) : position(rectangle.position), size(rectangle.size) {
			// ...
		}

		constexpr inline Rectangle(Rectangle&& rectangle) noexcept : position(std::move(rectangle.position)), size(std::move(rectangle.size)) {
			// ...
		}

		constexpr inline Rectangle(const Vector2<TComponent>& position, const Vector2<TComponent>& size) : position(position), size(size) {
			// ...
		}

		constexpr inline Rectangle(Vector2<TComponent>&& position, Vector2<TComponent>&& size) noexcept : position(position), size(size) {
			// ...
		}

		constexpr inline bool IsContained(const Vector2<TComponent>& position) const noexcept {
			return GetBounds().IsContained(position);
		}

		constexpr inline Rectangle<TComponent> GetCorrected() const noexcept {
			return Rectangle<TComponent>(
				Vector2<TComponent>(std::min(position.x, position.x + size.x), std::min(position.y, position.y + size.y)),
				Vector2<TComponent>(std::abs(size.x), std::abs(size.y))
			);
		}
		
		constexpr inline Rectangle<TComponent>& GetCorrected(Rectangle<TComponent>& result) const noexcept {
			return result = GetCorrected();
		}

		template <typename TReturn>
		constexpr inline Rectangle<TReturn> GetConverted() const noexcept {
			return Rectangle<TReturn>(position.template GetConverted<TReturn>(), size.template GetConverted<TReturn>());
		}

		template <typename TReturn>
		constexpr inline Rectangle<TReturn>& GetConverted(Bounds<TReturn>& result) const noexcept {
			return result = GetConverted<TReturn>();
		}

		constexpr inline Bounds<TComponent> GetBounds(EAlignment alignment) const noexcept {
			switch (alignment) {
			case EAlignment::TopLeft:
				return Bounds<TComponent>(position.y, position.y - size.y, position.x, position.x + size.x);
				break;
			case EAlignment::TopRight:
				return Bounds<TComponent>(position.y, position.y - size.y, position.x - size.x, position.x);
				break;
			case EAlignment::BottomLeft:
				return Bounds<TComponent>(position.y + size.y, position.y, position.x, position.x + size.x);
				break;
			case EAlignment::BottomRight:
				return Bounds<TComponent>(position.y + size.y, position.y, position.x - size.x, position.x);
				break;
			case EAlignment::Center:
				return Bounds<TComponent>(position.y - (size.y / static_cast<TComponent>(2)), position.y + (size.y / static_cast<TComponent>(2)), position.x - (size.x / static_cast<TComponent>(2)), position.x + (size.x / static_cast<TComponent>(2)));
				break;
			}
		}

		constexpr inline Bounds<TComponent>& GetBounds(EAlignment alignment, Bounds<TComponent>& result) const noexcept {
			return result = GetBounds(alignment);
		}

		constexpr inline Rectangle<TComponent>& operator =(const Rectangle<TComponent>& rectangle) {
			position = rectangle.position;
			size = rectangle.size;
			return *this;
		}

		constexpr inline Rectangle<TComponent>& operator =(Rectangle<TComponent>&& rectangle) noexcept {
			position = std::move(rectangle.position);
			size = std::move(rectangle.size);
			return *this;
		}

		constexpr inline bool operator ==(const Rectangle<TComponent>& rectangle) const noexcept {
			return (position == rectangle.position) && (size == rectangle.size);
		}

		constexpr inline bool operator !=(const Rectangle<TComponent>& rectangle) const noexcept {
			return (position != rectangle.position) || (size != rectangle.size);
		}

		constexpr inline Rectangle<TComponent>& operator +=(const Vector2<TComponent>& offset) noexcept {
			position += offset;
			return *this;
		}

		constexpr inline Rectangle<TComponent> operator +(const Vector2<TComponent>& offset) const noexcept {
			Rectangle<TComponent> ret(*this);
			return ret += offset;
		}

		constexpr inline Rectangle<TComponent>& operator -=(const Vector2<TComponent>& offset) noexcept {
			position -= offset;
			return *this;
		}

		constexpr inline Rectangle<TComponent> operator -(const Vector2<TComponent>& offset) const noexcept {
			Rectangle<TComponent> ret(*this);
			return ret -= offset;
		}
	};
}
