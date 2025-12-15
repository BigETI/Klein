#pragma once

#include "Utility.hpp"

namespace Klein::Math {
	class Easing {
	public:
		Easing() = delete;
		Easing(const Easing&) = delete;
		Easing(Easing&&) noexcept = delete;

		template <typename TValue>
		constexpr inline static TValue EaseIn(TValue x) noexcept {
			return GetLinearInterpolated(GetLinearInterpolated(x * static_cast<TValue>(-1), static_cast<TValue>(1), x), x, x);
		}
		
		template <typename TValue>
		constexpr inline static TValue EaseOut(TValue x) noexcept {
			return GetLinearInterpolated(x, GetLinearInterpolated(x, static_cast<TValue>(1), x), x);
		}
		
		template <typename TValue>
		constexpr inline static TValue EaseInOut(TValue x) noexcept {
			return GetLinearInterpolated(EaseIn(x), EaseOut(x), x);
		}

		Easing& operator =(const Easing&) = delete;
		Easing& operator =(Easing&&) noexcept = delete;
	};
}
