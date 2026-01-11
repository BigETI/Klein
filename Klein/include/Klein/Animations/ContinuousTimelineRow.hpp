#pragma once

#include <chrono>
#include <cstddef>
#include <optional>

#include "../Math/Easing.hpp"
#include "ETimeEvaluationMode.hpp"
#include "EvaluatedTimePointIndices.hpp"
#include "InterpolatableElement.hpp"
#include "TimelineRow.hpp"
#include "TimelineRowElement.hpp"

namespace Klein::Animations {

	template <typename TElement>
	class ContinuousTimelineRow : public TimelineRow<InterpolatableElement<TElement>> {
	public:

		constexpr inline bool TryAppending(const TElement& element, std::chrono::high_resolution_clock::duration duration, float easingIn = 1.0f, float easingOut = 1.0f, bool isLeftBroken = false, bool isRightBroken = false, std::size_t* outIndex = nullptr) {
			return TimelineRow<InterpolatableElement<TElement>>::TryAppending(InterpolatableElement<TElement> {.element = element, .easingIn = easingIn, .easingOut = easingOut, .isLeftBroken = isLeftBroken, .isRightBroken = isRightBroken }, duration, outIndex);
		}

		constexpr inline bool TryAppending(TElement&& element, std::chrono::high_resolution_clock::duration duration, float easingIn = 1.0f, float easingOut = 1.0f, bool isLeftBroken = false, bool isRightBroken = false, std::size_t* outIndex = nullptr) {
			return TimelineRow<InterpolatableElement<TElement>>::TryAppending(InterpolatableElement<TElement> {.element = element, .easingIn = easingIn, .easingOut = easingOut, .isLeftBroken = isLeftBroken, .isRightBroken = isRightBroken }, duration, outIndex);
		}

		constexpr inline bool TryInserting(const TElement& element, std::chrono::high_resolution_clock::duration timePoint, std::chrono::high_resolution_clock::duration duration, float easingIn = 1.0f, float easingOut = 1.0f, bool isLeftBroken = false, bool isRightBroken = false, std::size_t* outIndex = nullptr) {
			return TimelineRow<InterpolatableElement<TElement>>::TryInserting(InterpolatableElement<TElement> {.element = element, .easingIn = easingIn, .easingOut = easingOut, .isLeftBroken = isLeftBroken, .isRightBroken = isRightBroken }, timePoint, duration, outIndex);
		}

		constexpr inline bool TryInserting(TElement&& element, std::chrono::high_resolution_clock::duration timePoint, std::chrono::high_resolution_clock::duration duration, float easingIn = 1.0f, float easingOut = 1.0f, bool isLeftBroken = false, bool isRightBroken = false, std::size_t* outIndex = nullptr) {
			return TimelineRow<InterpolatableElement<TElement>>::TryInserting(InterpolatableElement<TElement> {.element = element, .easingIn = easingIn, .easingOut = easingOut, .isLeftBroken = isLeftBroken, .isRightBroken = isRightBroken }, timePoint, duration, outIndex);
		}

		constexpr inline std::optional<TElement> GetEvaluatedContinousValue(std::chrono::high_resolution_clock::duration timePoint, ETimeEvaluationMode timeEvaluationMode) const noexcept {
			if (std::optional<EvaluatedTimePointIndices> evaluated_time_point_indices = TimelineRow<InterpolatableElement<TElement>>::GetEvaluatedTimePointIndices(timePoint, timeEvaluationMode)) {
				const TimelineRowElement<InterpolatableElement<TElement>>& left_interpolatable_element(TimelineRow<InterpolatableElement<TElement>>::GetElements().at(evaluated_time_point_indices->leftIndex));
				const TimelineRowElement<InterpolatableElement<TElement>>& right_interpolatable_element(TimelineRow<InterpolatableElement<TElement>>::GetElements().at(evaluated_time_point_indices->rightIndex));
				if ((evaluated_time_point_indices->leftIndex == evaluated_time_point_indices->rightIndex) || right_interpolatable_element.element.isLeftBroken) {
					return left_interpolatable_element.element.element;
				}
				if (left_interpolatable_element.element.isRightBroken) {
					return right_interpolatable_element.element.element;
				}
				return std::lerp(left_interpolatable_element.element.element, right_interpolatable_element.element.element, Klein::Math::Easing::GetEasedInOut(std::chrono::duration<float>(evaluated_time_point_indices->progressTime).count() / std::chrono::duration<float>(evaluated_time_point_indices->transitionTime).count(), left_interpolatable_element.element.easingOut, right_interpolatable_element.element.easingIn));
			}
			return std::nullopt;
		}
	};
}
