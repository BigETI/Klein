#pragma once

#include <chrono>

namespace Klein::Animations {

	template <typename TElement>
	struct TimelineRowElement {

		TElement element;

		std::chrono::high_resolution_clock::duration timePoint;
	};
}
