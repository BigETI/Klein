#pragma once

#include <cstddef>
#include <filesystem>
#include <span>
#include <string>

#include "../Engine.hpp"

namespace Klein::Raylib {
	class RaylibEngine : public Klein::Engine {
	public:
#ifdef IS_KLEIN_CXX_STD_17
		KLEIN_API RaylibEngine(const std::string& title, std::size_t width, std::size_t height, const tcb::span<const std::string> commandLineArguments);
		KLEIN_API RaylibEngine(const std::string& title, std::size_t width, std::size_t height, const tcb::span<const std::string> commandLineArguments, const std::filesystem::path& configurationFilePath);
#else
		KLEIN_API RaylibEngine(const std::string& title, std::size_t width, std::size_t height, const std::span<const std::string> commandLineArguments);
		KLEIN_API RaylibEngine(const std::string& title, std::size_t width, std::size_t height, const std::span<const std::string> commandLineArguments, const std::filesystem::path& configurationFilePath);
#endif
		RaylibEngine(const RaylibEngine&) = delete;
		RaylibEngine(RaylibEngine&&) = delete;

		RaylibEngine& operator =(const RaylibEngine&) = delete;
		RaylibEngine& operator =(RaylibEngine&&) = delete;

	private:

		void Initialize(const std::string& title, std::size_t width, std::size_t height);
	};
}
