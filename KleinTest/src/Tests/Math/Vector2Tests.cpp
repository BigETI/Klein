#include <string>

#include <lest/lest.hpp>

#include <Klein/Math/Vector2.hpp>

#include <KleinTest/Tests/Math/Vector2Tests.hpp>

using namespace std;

using namespace lest;

using namespace Klein::Math;

using namespace KleinTest::Tests::Math;

string& Vector2Tests::GetName(string& result) const {
	return result = "2D Vector";
}

tests& Vector2Tests::GetTests(tests& result) const {
	result.push_back(
		{
			CASE("Empty 2D vector is empty") {
				Vector2<float> vector;
				EXPECT(vector.x == 0.0f);
				EXPECT(vector.y == 0.0f);
			}
		}
	);
	result.push_back(
		{
			CASE("2D vector has correct values") {
				Vector2<float> vector(1234.0f, 5678.0f);
				EXPECT(vector.x == 1234.0f);
				EXPECT(vector.y == 5678.0f);
			}
		}
	);
	result.push_back(
		{
			CASE("2D vector is convertible") {
				Vector2<float> vector(Vector2<int>(1234, 5678).GetConverted<float>());
				EXPECT(vector.x == 1234.0f);
				EXPECT(vector.y == 5678.0f);
			}
		}
	);
	result.push_back(
		{
			CASE("2D vector length is correct") {
				EXPECT(Vector2<int>(1234, 5678).GetLength() == sqrt((1234.0 * 1234.0) + (5678.0 * 5678.0)));
			}
		}
	);
	result.push_back(
		{
			CASE("2D vector is normalized") {
				Vector2<int> vector(Vector2<int>(1234, 5678));
				EXPECT(vector.GetNormalized() == (vector.GetConverted<double>() / vector.GetLength()));
			}
		}
	);
	return result;
}
