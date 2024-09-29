#pragma once

#include <string>

#include <lest/lest.hpp>

#include "../ITests.hpp"

namespace NGETest::Tests::Math {

	class Vector2Tests : public NGETest::Tests::ITests {
	public:

		std::string& GetName(std::string& result) const override;
		lest::tests& GetTests(lest::tests& result) const override;
	};
}
