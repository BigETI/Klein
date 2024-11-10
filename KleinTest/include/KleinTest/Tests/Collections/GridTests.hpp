#pragma once

#include <string>

#include <lest/lest.hpp>

#include "../ITests.hpp"

namespace KleinTest::Tests::Collections {
	class GridTests : public KleinTest::Tests::ITests {

		std::string& GetName(std::string& result) const override;
		lest::tests& GetTests(lest::tests& result) const override;
	};
}
