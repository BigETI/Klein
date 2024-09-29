#pragma once

#include <string>
#include <utility>

#include "BaseStringHash.hpp"

namespace NGE::Hashing {
	using StringHash = BaseStringHash<std::string, std::hash<std::string>>;
}
