#pragma once

#include <chrono>
#include <cstddef>

namespace Klein::Animations {

	struct EvaluatedTimePointIndices {

		std::size_t leftIndex;

		std::size_t rightIndex;

		std::chrono::high_resolution_clock::duration progressTime;

		std::chrono::high_resolution_clock::duration transitionTime;
	};
}
