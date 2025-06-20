#include <algorithm>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <span>
#include <string>
#include <thread>

#include <Klein/Audio/IAudioDevice.hpp>
#include <Klein/Engine.hpp>
#include <Klein/InputSystem/IInputHandler.hpp>
#include <Klein/InputSystem/InputEvent.hpp>
#include <Klein/Math/Ratio.hpp>
#include <Klein/Rendering/IRenderer.hpp>
#include <Klein/Rendering/RenderingContext.hpp>
#include <Klein/ResourceManagement/FileSystem.hpp>
#include <Klein/SceneManagement/Node.hpp>

using namespace std;
using namespace std::chrono;
using namespace std::filesystem;
using namespace std::this_thread;

using namespace Klein;
using namespace Klein::Audio;
using namespace Klein::InputSystem;
using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::ResourceManagement;
using namespace Klein::SceneManagement;

const Ratio<unsigned int> defaultTargetGameTickRate(1000U);
const Ratio<unsigned int> defaultTargetFrameRate(1000U);

Engine::Engine(const span<const string> commandLineArguments) :
	targetGameTickRate(defaultTargetGameTickRate),
	targetFrameRate(defaultTargetFrameRate),
	isGameRunning(false),
	gameStartTimePoint(high_resolution_clock::time_point::min()),
	defaultAudioDeviceIndex(static_cast<size_t>(0)),
	exitCode(-1) {
	if (commandLineArguments.size() > static_cast<size_t>(0)) {
		path executable_path(commandLineArguments[static_cast<size_t>(0)]);
		if (executable_path.is_absolute() && is_regular_file(executable_path) && executable_path.has_parent_path()) {
			FileSystem::SetExecutableDirectoryPath(executable_path.parent_path());
		}
	}
	renderingContexts.emplace_back();
}

Engine::Engine(const span<const string> commandLineArguments, const path& configurationFilePath) : Engine(commandLineArguments) {
	// TODO: Parse configuration file
}

Engine::~Engine() {
	ClearScenes();
}

bool Engine::IsGameRunning() const noexcept {
	return isGameRunning;
}

high_resolution_clock::time_point Engine::GetGameStartTimePoint() const noexcept {
	return gameStartTimePoint;
}

const std::vector<InputEvent>& Engine::GetCurrentInputEvents() const noexcept {
	return currentInputEvents;
}

vector<InputEvent>& Engine::GetCurrentInputEvents(vector<InputEvent>& result) const {
	return result = currentInputEvents;
}

const vector<shared_ptr<Node>>& Engine::GetScenes() const noexcept {
	return scenes;
}

const vector<RenderingContext>& Engine::GetRenderingContexts() const noexcept {
	return renderingContexts;
}

vector<RenderingContext>& Engine::GetRenderingContexts() noexcept {
	return renderingContexts;
}

const vector<shared_ptr<IRenderer>>& Engine::GetRenderers() const noexcept {
	return renderers;
}

const vector<shared_ptr<IAudioDevice>>& Engine::GetAudioDevices() const noexcept {
	return audioDevices;
}

const vector<shared_ptr<IInputHandler>>& Engine::GetInputHandlers() const noexcept {
	return inputHandlers;
}

int Engine::Start() {
	if (!isGameRunning) {
		isGameRunning = true;
		high_resolution_clock::duration target_game_tick_time(
			nanoseconds(static_cast<long long>(targetGameTickRate.denominator) * 1000000000LL / static_cast<long long>(targetGameTickRate.numerator))
		);
		high_resolution_clock::duration target_frame_render_time(
			nanoseconds(static_cast<long long>(targetFrameRate.denominator) * 1000000000LL / static_cast<long long>(targetFrameRate.numerator))
		);
		high_resolution_clock::duration game_tick_time_debt(high_resolution_clock::duration::zero());
		high_resolution_clock::duration frame_render_time_debt(high_resolution_clock::duration::zero());
		high_resolution_clock::time_point now(high_resolution_clock::now());
		high_resolution_clock::time_point last_game_tick_time(now);
		high_resolution_clock::time_point last_rendered_frame_tick_time(now);
		while (isGameRunning) {
			now = high_resolution_clock::now();
			high_resolution_clock::duration game_tick_time(now - last_game_tick_time);
			if ((game_tick_time + game_tick_time_debt) >= target_game_tick_time) {
				last_game_tick_time = now;
				game_tick_time_debt += game_tick_time - target_game_tick_time;
				currentInputEvents.clear();
				for (const auto& input_handler : inputHandlers) {
					input_handler->FetchInputEvents(currentInputEvents);
				}
				for (const auto& input_event : currentInputEvents) {
					if (input_event.GetNameHash() == InputEvent::GetCloseWindowInputEvent().GetNameHash()) {
						Stop();
						break;
					}
				}
				for (const auto& scene : scenes) {
					scene->GameTickScripts(*this, game_tick_time);
				}
			}
			now = high_resolution_clock::now();
			high_resolution_clock::duration frame_render_time(now - last_rendered_frame_tick_time);
			if ((frame_render_time + frame_render_time_debt) >= target_frame_render_time) {
				last_rendered_frame_tick_time = now;
				frame_render_time_debt += frame_render_time - target_frame_render_time;
				for (const auto& scene : scenes) {
					scene->BeforeFrameRenderScripts(*this, frame_render_time);
				}
				for (const auto& scene : scenes) {
					scene->FrameRenderScripts(*this, frame_render_time);
				}
				for (auto& rendering_context : renderingContexts) {
					rendering_context.CommitElements();
					for (auto& renderer : renderers) {
						renderer->Render(rendering_context, frame_render_time);
					}
					rendering_context.Clear();
				}
			}
			now = high_resolution_clock::now();
			high_resolution_clock::duration remaining_game_tick_sleep_time(target_game_tick_time - (now - last_game_tick_time) - game_tick_time_debt);
			high_resolution_clock::duration remaining_frame_render_sleep_time(target_frame_render_time - (now - last_rendered_frame_tick_time) - frame_render_time_debt);
			high_resolution_clock::duration sleep_time(max(min(remaining_game_tick_sleep_time, remaining_frame_render_sleep_time), high_resolution_clock::duration::zero()));
			if (sleep_time > high_resolution_clock::duration::zero()) {
				sleep_for(sleep_time);
			}
		}
	}
	return exitCode;
}

void Engine::Stop() {
	Stop(0);
}

void Engine::Stop(int exitCode) {
	if (isGameRunning) {
		this->exitCode = exitCode;
		isGameRunning = false;
	}
}

shared_ptr<Node> Engine::CreateNewEmptyScene() {
	return CreateNewScene<Node>();
}

bool Engine::RemoveScene(const shared_ptr<Node>& scene) {
	const auto& it(find(scenes.begin(), scenes.end(), scene));
	bool ret(it != scenes.end());
	if (ret) {
		scene->Destroy();
		scene->FrameRenderScripts(*this, high_resolution_clock::duration::zero());
		scenes.erase(it);
	}
	return ret;
}

void Engine::ClearScenes() {
	for (const auto& scene : scenes) {
		scene->Destroy();
		scene->FrameRenderScripts(*this, high_resolution_clock::duration::zero());
	}
	scenes.clear();
}

bool Engine::AddRenderer(const shared_ptr<IRenderer>& renderer) {
	bool ret(renderer && (find(renderers.begin(), renderers.end(), renderer) == renderers.end()));
	if (ret) {
		renderers.push_back(renderer);
	}
	return ret;
}

bool Engine::RemoveRenderer(const shared_ptr<IRenderer>& renderer) {
	size_t old_size(renderers.size());
	renderers.erase(remove(renderers.begin(), renderers.end(), renderer), renderers.end());
	return old_size != renderers.size();
}

void Engine::ClearRenderers() noexcept {
	renderers.clear();
}

bool Engine::AddAudioDevice(const shared_ptr<IAudioDevice>& audioDevice) {
	bool ret(audioDevice && (find(audioDevices.begin(), audioDevices.end(), audioDevice) == audioDevices.end()));
	if (ret) {
		audioDevices.push_back(audioDevice);
	}
	return ret;
}

bool Engine::RemoveAudioDevice(const shared_ptr<IAudioDevice>& audioDevice) {
	size_t old_size(audioDevices.size());
	if (defaultAudioDeviceIndex > static_cast<size_t>(0)) {
		if (static_cast<ptrdiff_t>(defaultAudioDeviceIndex) >= (find(audioDevices.begin(), audioDevices.end(), audioDevice) - audioDevices.begin())) {
			--defaultAudioDeviceIndex;
		}
	}
	audioDevices.erase(remove(audioDevices.begin(), audioDevices.end(), audioDevice), audioDevices.end());
	return old_size != audioDevices.size();
}

void Engine::ClearAudioDevices() noexcept {
	audioDevices.clear();
	defaultAudioDeviceIndex = static_cast<size_t>(0);
}

size_t Engine::GetDefaultAudioDeviceIndex() const noexcept {
	return defaultAudioDeviceIndex;
}

bool Engine::SetDefaultAudioDeviceIndex(size_t defaultAudioDeviceIndex) noexcept {
	bool ret(defaultAudioDeviceIndex < audioDevices.size());
	if (ret) {
		this->defaultAudioDeviceIndex = defaultAudioDeviceIndex;
	}
	return ret;
}

shared_ptr<IAudioDevice> Engine::GetDefaultAudioDevice() const noexcept {
	return (defaultAudioDeviceIndex < audioDevices.size()) ? audioDevices.at(defaultAudioDeviceIndex) : nullptr;
}

bool Engine::SetDefaultAudioDevice(const std::shared_ptr<Klein::Audio::IAudioDevice>& audioDevice) noexcept {
	const auto& it(find(audioDevices.begin(), audioDevices.end(), audioDevice));
	bool ret(it != audioDevices.end());
	if (ret) {
		defaultAudioDeviceIndex = static_cast<size_t>(it - audioDevices.begin());
	}
	return ret;
}

bool Engine::AddInputHandler(const shared_ptr<IInputHandler>& inputHandler) {
	bool ret(inputHandler && (find(inputHandlers.begin(), inputHandlers.end(), inputHandler) == inputHandlers.end()));
	if (ret) {
		inputHandlers.push_back(inputHandler);
	}
	return ret;
}

bool Engine::RemoveInputHandler(const shared_ptr<IInputHandler>& inputHandler) {
	size_t old_size(inputHandlers.size());
	inputHandlers.erase(remove(inputHandlers.begin(), inputHandlers.end(), inputHandler), inputHandlers.end());
	return old_size != inputHandlers.size();
}

void Engine::ClearInputHandlers() noexcept {
	inputHandlers.clear();
}
