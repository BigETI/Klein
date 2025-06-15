#include <chrono>
#include <filesystem>
#include <memory>
#include <utility>

#include <Klein/Audio/IAudioDevice.hpp>
#include <Klein/Engine.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Audio/AudioPlayerScript.hpp>
#include <Klein/Scripting/Script.hpp>

using namespace std;
using namespace std::chrono;
using namespace std::filesystem;

using namespace Klein;
using namespace Klein::Audio;
using namespace Klein::ResourceManagement;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting;
using namespace Klein::Scripting::Audio;

AudioPlayerScript::AudioPlayerScript(Node* node) :
	Script(node),
	engine(nullptr),
	isMusic(false),
	isUsingCache(true),
	volume(1.0f),
	isPreloadingWhenAvailable(false),
	isEnqueuedForPlayback(false) {
	// ...
}

AudioPlayerScript::~AudioPlayerScript() noexcept {
	Stop();
}

const ResourceID& AudioPlayerScript::GetResourceID() const noexcept {
	return resourceID;
}

void AudioPlayerScript::SetResourceID(const ResourceID& resourceID, bool isMusic, bool isUsingCache) noexcept {
	this->resourceID = resourceID;
	this->isMusic = isMusic;
	this->isUsingCache = isUsingCache;
}

void AudioPlayerScript::SetResourceID(ResourceID&& resourceID, bool isMusic, bool isUsingCache) noexcept {
	this->resourceID = std::move(resourceID);
	this->isMusic = isMusic;
	this->isUsingCache = isUsingCache;
}

bool AudioPlayerScript::IsMusic() const noexcept {
	return isMusic;
}

bool AudioPlayerScript::Preload() noexcept {
	if (engine) {
		if (shared_ptr<IAudioDevice> default_audio_device = engine->GetDefaultAudioDevice()) {
			if (lastAudioDevice.expired() || !lastAudioClip || (lastAudioClip->IsMusic() != isMusic) || (lastAudioDevice.lock() != default_audio_device)) {
				lastAudioClip = default_audio_device->LoadAudioClip(resourceID, isMusic, isUsingCache);
				lastAudioDevice = default_audio_device;
			}
		}
	}
	return static_cast<bool>(lastAudioClip);
}

void AudioPlayerScript::PreloadWhenAvailable() noexcept {
	isPreloadingWhenAvailable = true;
}

bool AudioPlayerScript::Play(float volume) noexcept {
	this->volume = volume;
	return Preload() && lastAudioClip->Play(volume);
}

void AudioPlayerScript::PlayWhenAvailable(float volume) noexcept {
	if (engine) {
		Play(volume);
	}
	else {
		this->volume = volume;
		isEnqueuedForPlayback = true;
	}
}

bool AudioPlayerScript::Stop() noexcept {
	isEnqueuedForPlayback = false;
	return lastAudioClip && lastAudioClip->Stop();
}

bool AudioPlayerScript::IsPlaying() const noexcept {
	return lastAudioClip && lastAudioClip->IsPlaying();
}

void AudioPlayerScript::OnEnable(Engine& engine) {
	this->engine = &engine;
	if (isEnqueuedForPlayback) {
		isPreloadingWhenAvailable = false;
		isEnqueuedForPlayback = false;
		Play(volume);
	}
	else if (isPreloadingWhenAvailable) {
		isPreloadingWhenAvailable = false;
		Preload();
	}
}

void AudioPlayerScript::OnDisable(Engine& engine) {
	Stop();
	this->engine = nullptr;
}

void AudioPlayerScript::OnGameTick(Engine& engine, const high_resolution_clock::duration& deltaTime) {
	if (lastAudioClip) {
		lastAudioClip->Update();
	}
}
