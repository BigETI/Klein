#pragma once

#include <string>

#include <lest/lest.hpp>

namespace KleinTest::Tests {
	struct ITests {

		constexpr virtual ~ITests() noexcept {
			// ...
		}

		virtual std::string& GetName(std::string& result) const = 0;
		virtual lest::tests& GetTests(lest::tests& result) const = 0;
	};
}
