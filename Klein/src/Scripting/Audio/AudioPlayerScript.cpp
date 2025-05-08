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

AudioPlayerScript::AudioPlayerScript(Node* node) : Script(node), engine(nullptr), isMusic(false), isEnqueuedForPlayback(false) {
	// ...
}

AudioPlayerScript::~AudioPlayerScript() noexcept {
	Stop();
}

const ResourceID& AudioPlayerScript::GetResourceID() const noexcept {
	return resourceID;
}

void AudioPlayerScript::SetResourceID(const ResourceID& resourceID, bool isMusic) noexcept {
	this->resourceID = resourceID;
	this->isMusic = isMusic;
}

void AudioPlayerScript::SetResourceID(ResourceID&& resourceID, bool isMusic) noexcept {
	this->resourceID = std::move(resourceID);
	this->isMusic = isMusic;
}

bool AudioPlayerScript::IsMusic() const noexcept {
	return isMusic;
}

bool AudioPlayerScript::Play() noexcept {
	bool ret(false);
	if (engine) {
		if (shared_ptr<IAudioDevice> default_audio_device = engine->GetDefaultAudioDevice()) {
			shared_ptr<IAudioClip> audio_clip;
			if (lastAudioDevice.expired() || !lastAudioClip || (lastAudioClip->IsMusic() != isMusic) || (lastAudioDevice.lock() != default_audio_device)) {
				audio_clip = default_audio_device->LoadAudioClip(resourceID, isMusic);
				lastAudioDevice = default_audio_device;
				lastAudioClip = audio_clip;
			}
			if (lastAudioClip) {
				ret = lastAudioClip->Play();
			}
		}
	}
	return ret;
}

void AudioPlayerScript::PlayWhenAvailable() noexcept {
	if (engine) {
		Play();
	}
	else {
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
		isEnqueuedForPlayback = false;
		Play();
	}
}

void AudioPlayerScript::OnDisable(Engine& engine) {
	Stop();
	this->engine = nullptr;
}

void AudioPlayerScript::OnGameTick(Engine& engine, high_resolution_clock::duration deltaTime) {
	if (lastAudioClip) {
		lastAudioClip->Update();
	}
}
