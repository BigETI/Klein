#include <cstddef>
#include <filesystem>
#include <span>
#include <string>

#include <Klein/Engine.hpp>
#include <Klein/InputSystem/Raylib/RaylibInputHandler.hpp>
#include <Klein/Raylib/RaylibEngine.hpp>
#include <Klein/Rendering/Raylib/RaylibWindowRenderer.hpp>

using namespace std;
using namespace std::filesystem;

using namespace Klein;
using namespace Klein::InputSystem::Raylib;
using namespace Klein::Raylib;
using namespace Klein::Rendering::Raylib;

RaylibEngine::RaylibEngine(const string& title, size_t width, size_t height, const span<const string> commandLineArguments) : Engine(commandLineArguments) {
	Initialize(title, width, height);
}

RaylibEngine::RaylibEngine(const string& title, size_t width, size_t height, const span<const string> commandLineArguments, const path& configurationFilePath) : Engine(commandLineArguments, configurationFilePath) {
	Initialize(title, width, height);
}

void RaylibEngine::Initialize(const string& title, size_t width, size_t height) {
	AddRenderer(make_shared<RaylibWindowRenderer>(title, width, height));
	AddInputHandler(make_shared<RaylibInputHandler>());
}
