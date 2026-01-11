#pragma once

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "ETimeEvaluationMode.hpp"
#include "EvaluatedTimePointIndices.hpp"
#include "TimelineRowElement.hpp"

namespace Klein::Animations {

	template <typename TElement>
	class TimelineRow {
	public:

		TimelineRow() : duration(std::chrono::high_resolution_clock::duration::zero()) {
			// ...
		}

		TimelineRow(const TimelineRow& timelineRow) : elements(timelineRow.elements), duration(timelineRow.duration) {
			// ...
		}

		TimelineRow(TimelineRow&& timelineRow) noexcept : elements(std::move(timelineRow.elements)), duration(std::move(timelineRow.duration)) {
			// ...
		}

		constexpr inline const std::vector<TimelineRowElement<TElement>>& GetElements() const noexcept {
			return elements;
		}

		constexpr inline std::chrono::high_resolution_clock::duration GetDuration() const noexcept {
			return duration;
		}

		constexpr inline bool TryAppending(const TElement& element, std::chrono::high_resolution_clock::duration duration, std::size_t* outIndex = nullptr) {
			return TryAppendingInternal(element, duration, outIndex);
		}

		constexpr inline bool TryAppending(TElement&& element, std::chrono::high_resolution_clock::duration duration, std::size_t* outIndex = nullptr) {
			return TryAppendingInternal(element, duration, outIndex);
		}

		constexpr inline bool AppendDuration(std::chrono::high_resolution_clock::duration duration) {
			if (duration < std::chrono::high_resolution_clock::duration::zero()) {
				return false;
			}
			this->duration += duration;
			return true;
		}

		constexpr inline bool TryInserting(const TElement& element, std::chrono::high_resolution_clock::duration timePoint, std::chrono::high_resolution_clock::duration duration, std::size_t* outIndex = nullptr) {
			return TryInsertingInternal(element, timePoint, duration, outIndex);
		}

		constexpr inline bool TryInserting(TElement&& element, std::chrono::high_resolution_clock::duration timePoint, std::chrono::high_resolution_clock::duration duration, std::size_t* outIndex = nullptr) {
			return TryInsertingInternal(element, timePoint, duration, outIndex);
		}

		constexpr inline bool RemoveIndex(std::size_t index) noexcept {
			if (index >= elements.size()) {
				return false;
			}
			elements.erase(elements.begin() + index, elements.begin() + index);
			return true;
		}

		constexpr inline std::optional<EvaluatedTimePointIndices> GetEvaluatedTimePointIndices(std::chrono::high_resolution_clock::duration timePoint, ETimeEvaluationMode timeEvaluationMode) const noexcept {
			if (elements.size() <= static_cast<std::size_t>(0)) {
				return std::nullopt;
			}
			std::chrono::high_resolution_clock::duration bounded_time_point;
			switch (timeEvaluationMode) {
			case ETimeEvaluationMode::Unbounded:
				if ((timePoint < elements.at(static_cast<std::size_t>(0)).timePoint) || (timePoint > duration)) {
					return std::nullopt;
				}
				bounded_time_point = timePoint;
				break;
			case ETimeEvaluationMode::Clamp:
				bounded_time_point = std::clamp(timePoint, elements.at(static_cast<std::size_t>(0)).timePoint, duration);
				break;
			case ETimeEvaluationMode::Loop:
				bounded_time_point = (duration > std::chrono::high_resolution_clock::duration::zero()) ? (timePoint % duration) : std::chrono::high_resolution_clock::duration::zero();
				break;
			case ETimeEvaluationMode::Reflect:
				bounded_time_point = (duration > std::chrono::high_resolution_clock::duration::zero()) ? ((((timePoint / duration) % 2) == 0) ? (timePoint % duration) : (duration - (timePoint % duration))) : std::chrono::high_resolution_clock::duration::zero();
				break;
			}
			std::size_t index(((elements.size() * static_cast<std::size_t>(2)) - static_cast<std::size_t>(1)) / static_cast<std::size_t>(4));
			std::size_t left_element_count(index);
			std::size_t right_element_count(elements.size() - left_element_count - static_cast<std::size_t>(1));
			while (true) {
				const TimelineRowElement<TElement>& element(elements.at(index));
				if (bounded_time_point < element.timePoint) {
					if (index <= static_cast<std::size_t>(0)) {
						return EvaluatedTimePointIndices{ .leftIndex = static_cast<std::size_t>(0), .rightIndex = static_cast<std::size_t>(0), .progressTime = std::chrono::high_resolution_clock::duration::zero(), .transitionTime = std::chrono::high_resolution_clock::duration::zero() };
					}
					if (left_element_count <= static_cast<std::size_t>(0)) {
						return EvaluatedTimePointIndices{ .leftIndex = index - static_cast<std::size_t>(1), .rightIndex = index, .progressTime = bounded_time_point - elements.at(index - static_cast<std::size_t>(1)).timePoint, .transitionTime = std::clamp(element.timePoint - elements.at(index - static_cast<std::size_t>(1)).timePoint, std::chrono::high_resolution_clock::duration::zero(), duration) };
					}
					std::size_t local_element_count(left_element_count);
					std::size_t local_index(((local_element_count * static_cast<std::size_t>(2)) - static_cast<std::size_t>(1)) / static_cast<std::size_t>(4));
					left_element_count = local_index;
					right_element_count = local_element_count - left_element_count - static_cast<std::size_t>(1);
					index = index + local_index - local_element_count;

				}
				else if (bounded_time_point > element.timePoint) {
					if ((index + static_cast<std::size_t>(1)) >= elements.size()) {
						return EvaluatedTimePointIndices{ .leftIndex = elements.size() - static_cast<std::size_t>(1), .rightIndex = elements.size() - static_cast<std::size_t>(1), .progressTime = std::chrono::high_resolution_clock::duration::zero(), .transitionTime = std::chrono::high_resolution_clock::duration::zero() };
					}
					if (right_element_count <= static_cast<std::size_t>(0)) {
						return EvaluatedTimePointIndices{ .leftIndex = index, .rightIndex = index + static_cast<std::size_t>(1), .progressTime = bounded_time_point - element.timePoint, .transitionTime = std::clamp(elements.at(index + static_cast<std::size_t>(1)).timePoint - element.timePoint, std::chrono::high_resolution_clock::duration::zero(), duration) };
					}
					std::size_t local_element_count(right_element_count);
					std::size_t local_index(((local_element_count * static_cast<std::size_t>(2)) - static_cast<std::size_t>(1)) / static_cast<std::size_t>(4));
					left_element_count = local_index;
					right_element_count = local_element_count - left_element_count - static_cast<std::size_t>(1);
					index = index + local_index + static_cast<std::size_t>(1);
				}
				else {
					return EvaluatedTimePointIndices{ .leftIndex = index, .rightIndex = index, .progressTime = std::chrono::high_resolution_clock::duration::zero(), .transitionTime = std::chrono::high_resolution_clock::duration::zero() };
				}
			}
			return std::nullopt;
		}

		constexpr inline std::optional<TElement> GetEvaluatedDiscreteValue(std::chrono::high_resolution_clock::duration timePoint, ETimeEvaluationMode timeEvaluationMode) const noexcept {
			if (std::optional<EvaluatedTimePointIndices> evaluated_time_point_indices = GetEvaluatedTimePointIndices(timePoint, timeEvaluationMode)) {
				return elements.at(evaluated_time_point_indices->leftIndex).element;
			}
			return std::nullopt;
		}

		constexpr inline TimelineRow& operator =(const TimelineRow& timelineRow) {
			elements = timelineRow.elements;
			duration = timelineRow.duration;
			return *this;
		}

		constexpr inline TimelineRow& operator =(TimelineRow&& timelineRow) noexcept {
			elements = std::move(timelineRow.elements);
			duration = std::move(timelineRow.duration);
			return *this;
		}

	private:

		constexpr inline bool TryAppendingInternal(auto element, std::chrono::high_resolution_clock::duration duration, std::size_t* outIndex) {
			if (duration < std::chrono::high_resolution_clock::duration::zero()) {
				return false;
			}
			elements.emplace_back(TimelineRowElement<TElement> {.element = std::forward<TElement>(element), .timePoint = this->duration });
			this->duration += duration;
			return true;
		}

		constexpr inline bool TryInsertingInternal(auto element, std::chrono::high_resolution_clock::duration timePoint, std::chrono::high_resolution_clock::duration duration, std::size_t* outIndex) {
			if ((timePoint < std::chrono::high_resolution_clock::duration::zero()) || (duration < std::chrono::high_resolution_clock::duration::zero())) {
				return false;
			}
			std::size_t index(static_cast<std::size_t>(0));
			bool is_replacing(false);
			for (const auto& element : elements) {
				if (timePoint < element.timePoint) {
					break;
				}
				else if (timePoint > element.timePoint) {
					++index;
					continue;
				}
				else {
					is_replacing = true;
					break;
				}
			}

			if (is_replacing) {
				elements[index] = TimelineRowElement<TElement>{ .element = std::forward<TElement>(element), .timePoint = timePoint };
			}
			else if (index < elements.size()) {
				elements.insert(elements.begin() + index, TimelineRowElement<TElement> {.element = std::forward<TElement>(element), .timePoint = timePoint });
			}
			else {
				elements.emplace_back(TimelineRowElement<TElement> {.element = std::forward<TElement>(element), .timePoint = timePoint });
			}
			this->duration = std::max(this->duration, timePoint + duration);
			if (outIndex) {
				*outIndex = index;
			}
			return true;
		}

		std::vector<TimelineRowElement<TElement>> elements;

		std::chrono::high_resolution_clock::duration duration;
	};
}
