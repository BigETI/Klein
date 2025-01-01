#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "../Math/Vector2.hpp"
#include "EGridResizingRule.hpp"

namespace Klein::Collections {
	template <typename TCell>
	struct ResizableGrid {
	public:

		ResizableGrid() {
			// ...
		}
		
		ResizableGrid(const ResizableGrid<TCell>& resizableGrid) : size(resizableGrid.size), cells(resizableGrid.cells) {
			// ...
		}
		
		ResizableGrid(ResizableGrid<TCell>&& resizableGrid) noexcept : size(std::move(resizableGrid.size)), cells(std::move(resizableGrid.cells)) {
			// ...
		}

		ResizableGrid(std::size_t width, std::size_t height, const TCell& defaultValue) : size(width, height), cells(width * height, defaultValue) {
			// ...
		}
		
		ResizableGrid(const Klein::Math::Vector2<std::size_t>& size, const TCell& defaultValue) : size(size), cells(size.x * size.y, defaultValue) {
			// ...
		}

		constexpr inline const Klein::Math::Vector2<std::size_t>& GetSize() const noexcept {
			return size;
		}

		constexpr inline const std::vector<TCell>& GetCells() const noexcept {
			return cells;
		}

		constexpr inline bool IsWithinBounds(std::size_t x, std::size_t y) const noexcept {
			return IsWithinBounds(Klein::Math::Vector2<std::size_t>(x, y));
		}
		
		constexpr inline bool IsWithinBounds(const Klein::Math::Vector2<std::size_t>& position) const noexcept {
			return (position.x < size.x) && (position.y < size.y);
		}

		constexpr inline std::size_t GetIndex(std::size_t x, std::size_t y) const {
			return GetIndex(Klein::Math::Vector2<std::size_t>(x, y));
		}
		
		constexpr inline std::size_t GetIndex(const Klein::Math::Vector2<std::size_t>& position) const {
			if (!IsWithinBounds(position)) {
				throw std::invalid_argument("X, and Y are out of bounds.");
			}
			return GetIndexWithoutBoundsCheck(position);
		}

		constexpr const TCell& GetCell(std::size_t x, std::size_t y) const
		{
			return GetCell(Klein::Math::Vector2<std::size_t>(x, y));
		}
		
		constexpr TCell& GetCell(std::size_t x, std::size_t y)
		{
			return GetCell(Klein::Math::Vector2<std::size_t>(x, y));
		}
		
		constexpr const TCell& GetCell(const Klein::Math::Vector2<std::size_t>& position) const
		{
			return cells.at(GetIndex(position));
		}
		
		constexpr TCell& GetCell(const Klein::Math::Vector2<std::size_t>& position)
		{
			return cells.at(GetIndex(position));
		}

		constexpr inline bool TryGettingCell(std::size_t x, std::size_t y, TCell& result) const noexcept {
			return TryGettingCell(Klein::Math::Vector2<std::size_t>(x, y), result);
		}
		
		constexpr inline bool TryGettingCell(const Klein::Math::Vector2<std::size_t>& position, TCell& result) const noexcept {
			bool ret(IsWithinBounds(position));
			if (ret) {
				result = cells.at(GetIndexWithoutBoundsCheck(position));
			}
			return ret;
		}
		
		constexpr inline const bool SetCell(std::size_t x, std::size_t y, const TCell& cell) noexcept
		{
			return SetCell(Klein::Math::Vector2<std::size_t>(x, y));
		}
		
		constexpr inline const bool SetCell(const Klein::Math::Vector2<std::size_t>& position, const TCell& cell) noexcept
		{
			bool ret(IsWithinBounds(position));
			if (ret) {
				cells[GetIndexWithoutBoundsCheck(position)] = cell;
			}
			return ret;
		}

		constexpr void Resize(const Klein::Math::Vector2<std::size_t>& size, EGridResizingRule gridResizingRule, const TCell* optionalDefaultCell = nullptr) {
			if (this->size != size) {
				std::size_t new_cell_count(size.x * size.y);
				if (gridResizingRule == EGridResizingRule::Naive) {
					if (optionalDefaultCell) {
						cells.resize(new_cell_count, *optionalDefaultCell);
					}
					else {
						cells.resize(new_cell_count);
					}
				}
				else {
					std::size_t old_cell_count(cells.size());

					Klein::Math::Vector2<long long> offset;
					switch (gridResizingRule) {
					case EGridResizingRule::Naive:
						break;
					case EGridResizingRule::TopLeftAligned:
						break;
					case EGridResizingRule::TopRightAligned:
						offset.x = static_cast<long long>(this->size.x) - static_cast<long long>(size.x);
						break;
					case EGridResizingRule::BottomLeftALigned:
						offset.y = static_cast<long long>(this->size.y) - static_cast<long long>(size.y);
						break;
					case EGridResizingRule::BottomRightAligned:
						offset.x = static_cast<long long>(this->size.x) - static_cast<long long>(size.x);
						offset.y = static_cast<long long>(this->size.y) - static_cast<long long>(size.y);
						break;
					}

					if (old_cell_count < new_cell_count) {
						cells.resize(new_cell_count);
						for (long long new_cell_index(static_cast<long long>(new_cell_count) - 1LL); new_cell_index >= 0LL; new_cell_index--) {
							Klein::Math::Vector2<long long> new_position(
								new_cell_count % static_cast<long long>(size.x),
								new_cell_count / static_cast<long long>(size.x)
							);
							Klein::Math::Vector2<long long> old_position = new_position + offset;
							if ((old_position.x >= 0LL) &&
								(old_position.x < static_cast<long long>(this->size.x)) &&
								(old_position.y >= 0LL) &&
								(old_position.y < static_cast<long long>(this->size.y))) {
								std::size_t old_cell_index(old_position.x + (old_position.y * this->size.x));
								cells[static_cast<std::size_t>(new_cell_index)] = cells.at(old_cell_index);
							}
							else if (optionalDefaultCell) {
								cells[static_cast<std::size_t>(new_cell_index)] = *optionalDefaultCell;
							}
						}
					}
					else {
						for (long long old_cell_index(static_cast<long long>(old_cell_count) - 1LL); old_cell_index >= 0LL; old_cell_index--) {
							Klein::Math::Vector2<long long> old_position(
								old_cell_count % static_cast<long long>(this->size.x),
								old_cell_count / static_cast<long long>(this->size.x)
							);
							Klein::Math::Vector2<long long> new_position = old_position - offset;
							if ((new_position.x >= 0LL) &&
								(new_position.x < static_cast<long long>(size.x)) &&
								(new_position.y >= 0LL) &&
								(new_position.y < static_cast<long long>(size.y))) {
								std::size_t new_cell_index(new_position.x + (new_position.y * size.x));
								cells[new_cell_index] = cells.at(static_cast<std::size_t>(old_cell_index));
							}
						}
					}
				}
				this->size = size;
			}
		}

		constexpr inline ResizableGrid<TCell>& operator =(const ResizableGrid<TCell>& resizableGrid) {
			size = resizableGrid.size;
			cells = resizableGrid.cells;
			return *this;
		}

		constexpr inline ResizableGrid<TCell>& operator =(ResizableGrid<TCell>&& resizableGrid) noexcept {
			size = std::move(resizableGrid.size);
			cells = std::move(resizableGrid.cells);
			return *this;
		}

		constexpr inline const TCell& operator [](const Klein::Math::Vector2<std::size_t>& position) const {
			return GetCell(position);
		}
		
		constexpr inline TCell& operator [](const Klein::Math::Vector2<std::size_t>& position) {
			return GetCell(position);
		}

		constexpr inline bool operator ==(ResizableGrid<TCell>& resizableGrid) const noexcept {
			bool ret(size == resizableGrid.size);
			if (ret) {
				for (std::size_t cell_index(static_cast<std::size_t>(0U)); cell_index != cells.size(); cell_index++) {
					if (cells.at(cell_index) != resizableGrid.cells.at(cell_index)) {
						ret = false;
						break;
					}
				}
			}
			return ret;
		}

		constexpr inline bool operator !=(ResizableGrid<TCell>& resizableGrid) const noexcept {
			return !(*this == resizableGrid);
		}

	private:

		Klein::Math::Vector2<std::size_t> size;

		std::vector<TCell> cells;

		constexpr inline std::size_t GetIndexWithoutBoundsCheck(const Klein::Math::Vector2<std::size_t>& position) const noexcept {
			return position.x + (position.y * size.x);
		}
	};
}
