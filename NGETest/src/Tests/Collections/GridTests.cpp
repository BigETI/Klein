#include <cstddef>
#include <string>

#include <NGE/Collections/Grid.hpp>
#include <NGE/Math/Vector2.hpp>

#include <NGETest/Tests/Collections/GridTests.hpp>

using namespace std;

using namespace lest;

using namespace NGE::Collections;
using namespace NGE::Math;

using namespace NGETest::Tests::Collections;

string& GridTests::GetName(string& result) const {
	return result = "Grid";
}

tests& GridTests::GetTests(tests& result) const {
	result.push_back(
		{
			CASE("Empty grid is empty") {
				Grid<int, 0, 0> grid;
				EXPECT(grid.Width == static_cast<size_t>(0));
				EXPECT(grid.Height == static_cast<size_t>(0));
				EXPECT(grid.Size == Vector2<size_t>());
			}
		}
	);
	result.push_back(
		{
			CASE("Grid has default cell") {
				Grid<int, 3, 3> grid(1234);
				EXPECT(grid.Width == static_cast<size_t>(3));
				EXPECT(grid.Height == static_cast<size_t>(3));
				EXPECT(grid.Size == Vector2<size_t>(3, 3));
				EXPECT(grid.GetCell(0, 0) == 1234);
				EXPECT(grid.GetCell(1, 0) == 1234);
				EXPECT(grid.GetCell(2, 0) == 1234);
				EXPECT(grid.GetCell(0, 1) == 1234);
				EXPECT(grid.GetCell(1, 1) == 1234);
				EXPECT(grid.GetCell(2, 1) == 1234);
				EXPECT(grid.GetCell(0, 2) == 1234);
				EXPECT(grid.GetCell(1, 2) == 1234);
				EXPECT(grid.GetCell(2, 2) == 1234);
			}
		}
	);
	result.push_back(
		{
			CASE("Grid has valid entries") {
				Grid<int, 3, 3> grid(
					{
						1234, 2345, 3456,
						4567, 5678, 6789,
						7890, 8901, 9012
					}
				);
				EXPECT(grid.Width == static_cast<size_t>(3));
				EXPECT(grid.Height == static_cast<size_t>(3));
				EXPECT(grid.Size == Vector2<size_t>(3, 3));
				EXPECT(grid.GetCell(0, 0) == 1234);
				EXPECT(grid.GetCell(1, 0) == 2345);
				EXPECT(grid.GetCell(2, 0) == 3456);
				EXPECT(grid.GetCell(0, 1) == 4567);
				EXPECT(grid.GetCell(1, 1) == 5678);
				EXPECT(grid.GetCell(2, 1) == 6789);
				EXPECT(grid.GetCell(0, 2) == 7890);
				EXPECT(grid.GetCell(1, 2) == 8901);
				EXPECT(grid.GetCell(2, 2) == 9012);
			}
		}
	);
	return result;
}
