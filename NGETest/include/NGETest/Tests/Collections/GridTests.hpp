#pragma once

#include <string>

#include <lest/lest.hpp>

#include "../ITests.hpp"

namespace NGETest::Tests::Collections {
	class GridTests : public NGETest::Tests::ITests {

		std::string& GetName(std::string& result) const override;
		lest::tests& GetTests(lest::tests& result) const override;
	};
}
