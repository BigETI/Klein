#include <memory>
#include <string>
#include <vector>

#include <lest/lest.hpp>

#include <KleinTest/Tests/Collections/GridTests.hpp>
#include <KleinTest/Tests/ITests.hpp>
#include <KleinTest/Tests/Math/Vector2Tests.hpp>

using namespace std;

using namespace lest;

using namespace KleinTest::Tests;
using namespace KleinTest::Tests::Collections;
using namespace KleinTest::Tests::Math;

const vector<shared_ptr<ITests>> specifications = {
	make_shared<GridTests>(),
	make_shared<Vector2Tests>()
};

int main(int argc, char* argv[]) {
	int ret(0);
	for (const shared_ptr<ITests>& specification : specifications) {
		string name;
		tests tests;
		specification->GetName(name);
		specification->GetTests(tests);
		if (tests.size() > 0U) {
			cout << "Running " << tests.size() << " test" << ((tests.size() > 1U) ? "s" : "") << " for \"" << name << "\"" << endl;
			int fail_count(run(tests, argc, argv));
			cout << (tests.size() - fail_count) << " out of " << tests.size() << " test" << ((tests.size() > 1U) ? "s" : "") << " have passed." << endl;
			if (fail_count) {
				cerr << fail_count << " of " << tests.size() << " test" << ((tests.size() > 1U) ? "s" : "") << " in \"" << name << "\" have failed!" << endl;
			}
			ret += fail_count;
			cout << endl;
		}
		else {
			cerr << "No tests are specified for \"" << name << "\"." << endl << endl;
		}
	}
	if (ret) {
		cerr << ret << " test" << ((ret > 1) ? "s have" : " has") << " failed!" << endl;
	}
	else {
		cout << "All tests have passed!" << endl;
	}
	return ret;
}
