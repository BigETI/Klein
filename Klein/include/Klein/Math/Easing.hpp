#pragma once

#include <cmath>

namespace Klein::Math {
	class Easing {
	public:
		Easing() = delete;
		Easing(const Easing&) = delete;
		Easing(Easing&&) noexcept = delete;

		template <typename TValue>
		constexpr static TValue GetEasedIn(TValue x) noexcept {
			return std::lerp(std::lerp(-x, static_cast<TValue>(1), x), x, x);
		}
		
		template <typename TValue>
		constexpr static TValue GetEasedOut(TValue x) noexcept {
			return std::lerp(x, std::lerp(x, static_cast<TValue>(1), x), x);
		}
		
		template <typename TValue>
		constexpr static TValue GetEasedInOut(TValue x) noexcept {
			return std::lerp(GetEasedIn(x), GetEasedOut(x), x);
		}

		template <typename TValue>
		constexpr static TValue GetEasedInOut(TValue x, TValue easeOut, TValue easeIn) noexcept {
			return std::lerp(std::lerp(x, GetEasedIn(x), easeOut), std::lerp(x, GetEasedOut(x), easeOut), x);
		}

		Easing& operator =(const Easing&) = delete;
		Easing& operator =(Easing&&) noexcept = delete;
	};
}
