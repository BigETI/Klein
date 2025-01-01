#pragma once

#include <cstddef>
#include <filesystem>
#include <span>
#include <string>

#include "../Engine.hpp"

namespace Klein::Raylib {
	class RaylibEngine : public Klein::Engine {
	public:

		KLEIN_API RaylibEngine(const std::string& title, std::size_t width, std::size_t height, const std::span<const std::string> commandLineArguments);
		KLEIN_API RaylibEngine(const std::string& title, std::size_t width, std::size_t height, const std::span<const std::string> commandLineArguments, const std::filesystem::path& configurationFilePath);

		RaylibEngine(const RaylibEngine&) = delete;
		RaylibEngine(RaylibEngine&&) = delete;

		RaylibEngine& operator =(const RaylibEngine&) = delete;
		RaylibEngine& operator =(RaylibEngine&&) = delete;

	private:

		void Initialize(const std::string& title, std::size_t width, std::size_t height);
	};
}
