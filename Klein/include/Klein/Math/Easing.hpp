#pragma once

#include <cmath>
#include <numbers>

namespace Klein::Math {
	class Easing {
	public:
		Easing() = delete;
		Easing(const Easing&) = delete;
		Easing(Easing&&) noexcept = delete;

		template <typename TValue>
		constexpr static TValue EaseIn(TValue x) noexcept {
			return std::lerp(std::lerp(x * static_cast<TValue>(-1), static_cast<TValue>(1), x), x, x);
		}
		
		template <typename TValue>
		constexpr static TValue EaseOut(TValue x) noexcept {
			return std::lerp(x, std::lerp(x, static_cast<TValue>(1), x), x);
		}
		
		template <typename TValue>
		constexpr static TValue EaseInOut(TValue x) noexcept {
			return std::lerp(EaseIn(x), EaseOut(x), x);
		}

		Easing& operator =(const Easing&) = delete;
		Easing& operator =(Easing&&) noexcept = delete;
	};
}
