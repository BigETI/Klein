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
			CASE("Grid has valid entries") {
				Grid<int, 3, 3> grid(
					{
						123, 234, 345,
						456, 567, 678,
						789, 890, 901
					}
				);
				EXPECT(grid.Width == static_cast<size_t>(3));
				EXPECT(grid.Height == static_cast<size_t>(3));
				EXPECT(grid.Size == Vector2<size_t>(3, 3));
				EXPECT(grid.GetCell(0, 0) == 123);
				EXPECT(grid.GetCell(1, 0) == 234);
				EXPECT(grid.GetCell(2, 0) == 345);
				EXPECT(grid.GetCell(0, 1) == 456);
				EXPECT(grid.GetCell(1, 1) == 567);
				EXPECT(grid.GetCell(2, 1) == 678);
				EXPECT(grid.GetCell(0, 2) == 789);
				EXPECT(grid.GetCell(1, 2) == 890);
				EXPECT(grid.GetCell(2, 2) == 901);
			}
		}
	);
	return result;
}
