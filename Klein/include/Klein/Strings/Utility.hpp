#pragma once

#include <string_view>

namespace Klein::Strings {

	constexpr inline static bool IsStartingWith(std::string_view str, std::string_view prefix) noexcept {
#ifdef IS_KLEIN_CXX_STD_17
		if (str.size() < prefix.size()) {
			return false;
		}
		return str.substr(static_cast<size_t>(0), prefix.size()) == prefix;
#else
		return str.starts_with(prefix);
#endif
	}

	constexpr inline static bool IsEndingWith(std::string_view str, std::string_view suffix) noexcept {
#ifdef IS_KLEIN_CXX_STD_17
		if (str.size() < suffix.size()) {
			return false;
		}
		return str.substr(str.size() - suffix.size(), suffix.size()) == suffix;
#else
		return str.ends_with(suffix);
#endif
	}

	constexpr inline static bool IsContaining(std::string_view str, std::string_view infix) noexcept {
#ifdef IS_KLEIN_CXX_STD_17
		std::string_view sub_str(str);
		while ((sub_str.size() > static_cast<size_t>(0)) && (sub_str.size() >= infix.size())) {
			if (IsStartingWith(sub_str, infix)) {
				return true;
			}
			sub_str = sub_str.substr(static_cast<size_t>(1), sub_str.size() - static_cast<size_t>(1));
		}
		return false;
#else
		return str.contains(infix);
#endif
	}
}
