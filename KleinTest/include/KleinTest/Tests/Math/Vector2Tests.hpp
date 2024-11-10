#pragma once

#include <string>

#include <lest/lest.hpp>

#include "../ITests.hpp"

namespace KleinTest::Tests::Math {

	class Vector2Tests : public KleinTest::Tests::ITests {
	public:

		std::string& GetName(std::string& result) const override;
		lest::tests& GetTests(lest::tests& result) const override;
	};
}
