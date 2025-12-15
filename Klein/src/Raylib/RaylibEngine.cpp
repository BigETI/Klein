#include <cstddef>
#include <filesystem>
#ifndef IS_KLEIN_CXX_STD_17
#	include <span>
#endif
#include <string>

#ifdef IS_KLEIN_CXX_STD_17
#	include <tcb/span.hpp>
#endif

#include <Klein/Audio/Raylib/RaylibAudioDevice.hpp>
#include <Klein/Engine.hpp>
#include <Klein/InputSystem/Raylib/RaylibInputHandler.hpp>
#include <Klein/Raylib/RaylibEngine.hpp>
#include <Klein/Rendering/Raylib/RaylibWindowRenderer.hpp>

using namespace std;
using namespace std::filesystem;
#ifdef IS_KLEIN_CXX_STD_17
using namespace tcb;
#endif
using namespace Klein;
using namespace Klein::Audio::Raylib;
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
	AddAudioDevice(make_shared<RaylibAudioDevice>());
	AddInputHandler(make_shared<RaylibInputHandler>());
}
