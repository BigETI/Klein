#pragma once

#ifndef IS_KLEIN_CXX_STD_17
#	include <cmath>
#endif

namespace Klein::Math {
	template <typename TValue>
	constexpr inline static TValue GetLinearInterpolated(TValue a, TValue b, TValue t) noexcept {
#ifdef IS_KLEIN_CXX_STD_17
		return a + (t * (b - a));
#else
		return std::lerp(a, b, t);
#endif
	}
}
