#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include "../Math/Vector2.hpp"
#include "EGridResizingRule.hpp"

namespace Klein::Collections {
	template <typename TCell, std::size_t W, std::size_t H>
	struct Grid {
	public:

		constexpr inline static const std::size_t Width = W;

		constexpr inline static const std::size_t Height = H;

		constexpr inline static const std::size_t CellCount = Width * Height;

		constexpr inline static const Klein::Math::Vector2<std::size_t> Size = Klein::Math::Vector2<std::size_t>(Width, Height);

		constexpr inline Grid() {
			// ...
		}

		constexpr inline Grid(const Grid<TCell, Width, Height>& grid) : cells(grid.cells) {
			// ...
		}

		constexpr inline Grid(Grid<TCell, Width, Height>&& grid) noexcept : cells(std::move(grid.cells)) {
			// ...
		}

		constexpr inline Grid(const std::array<TCell, CellCount>& cells) : cells(cells) {
			// ...
		}

		constexpr inline Grid(const TCell& defaultCell) {
			std::fill(cells.begin(), cells.end(), defaultCell);
		}

		constexpr inline Grid(std::array<TCell, CellCount>&& cells) noexcept : cells(cells) {
			// ...
		}

		constexpr inline const std::array<TCell, CellCount>& GetCells() const noexcept {
			return cells;
		}

		constexpr inline bool IsWithinBounds(std::size_t x, std::size_t y) const noexcept {
			return IsWithinBounds(Klein::Math::Vector2<std::size_t>(x, y));
		}

		constexpr inline bool IsWithinBounds(const Klein::Math::Vector2<std::size_t>& position) const noexcept {
			return (position.x < Width) && (position.y < Height);
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

		constexpr inline Grid<TCell, Width, Height>& operator =(const Grid<TCell, Width, Height>& grid) {
			cells = grid.cells;
			return *this;
		}

		constexpr inline Grid<TCell, Width, Height>& operator =(Grid<TCell, Width, Height>&& grid) noexcept {
			cells = std::move(grid.cells);
			return *this;
		}

		constexpr inline const TCell& operator [](const Klein::Math::Vector2<std::size_t>& position) const {
			return GetCell(position);
		}

		constexpr inline TCell& operator [](const Klein::Math::Vector2<std::size_t>& position) {
			return GetCell(position);
		}

		constexpr inline bool operator ==(Grid<TCell, Width, Height>& grid) const noexcept {
			bool ret(true);
			for (std::size_t cell_index(static_cast<std::size_t>(0U)); cell_index != cells.size(); cell_index++) {
				if (cells.at(cell_index) != grid.cells.at(cell_index)) {
					ret = false;
					break;
				}
			}
			return ret;
		}

		constexpr inline bool operator !=(Grid<TCell, Width, Height>& grid) const noexcept {
			return !(*this == grid);
		}

	private:

		std::array<TCell, CellCount> cells;

		constexpr inline std::size_t GetIndexWithoutBoundsCheck(const Klein::Math::Vector2<std::size_t>& position) const noexcept {
			return position.x + (position.y * Width);
		}
	};
}
