#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <variant>

#include <raylib.h>

#include <Klein/Audio/Raylib/RaylibAudioClip.hpp>
#include <Klein/ResourceManagement/FileSystem.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace Klein::Audio::Raylib;
using namespace Klein::ResourceManagement;

RaylibAudioClip::RaylibAudioClip(const Sound& sound) : soundOrMusic(sound) {
	// ...
}

RaylibAudioClip::RaylibAudioClip(const Music& music) : soundOrMusic(music) {
	// ...
}

RaylibAudioClip::~RaylibAudioClip() noexcept {
	Stop();
	if (holds_alternative<Sound>(soundOrMusic)) {
		UnloadSound(get<Sound>(soundOrMusic));
	}
	else if (holds_alternative<Music>(soundOrMusic)) {
		UnloadMusicStream(get<Music>(soundOrMusic));
	}
}

shared_ptr<RaylibAudioClip> RaylibAudioClip::Load(const ResourceID& resourceID, bool isMusic) noexcept {
	shared_ptr<RaylibAudioClip> ret;
	if (IsAudioDeviceReady()) {
		if (isMusic) {
			path path;
			Music music(LoadMusicStream(FileSystem::GetFilePathFromResourceID(resourceID, path).string().c_str()));
			if (IsMusicValid(music)) {
				ret = make_shared<RaylibAudioClip>(music);
			}
		}
		else {
			path path;
			Sound sound(LoadSound(FileSystem::GetFilePathFromResourceID(resourceID, path).string().c_str()));
			if (IsSoundValid(sound)) {
				ret = make_shared<RaylibAudioClip>(sound);
			}
		}
	}
	if (!ret) {
		cerr << "Failed to load audio clip with resource ID \"" << resourceID.GetString() << "\"" << " (" << resourceID.GetHash() << ")" << endl;
	}
	return ret;
}

bool RaylibAudioClip::Play() noexcept {
	bool ret(false);
	if (holds_alternative<Sound>(soundOrMusic)) {
		PlaySound(get<Sound>(soundOrMusic));
		ret = true;
	}
	else if (holds_alternative<Music>(soundOrMusic)) {
		PlayMusicStream(get<Music>(soundOrMusic));
		ret = true;
	}
	return ret;
}

bool RaylibAudioClip::Stop() noexcept {
	bool ret(false);
	if (holds_alternative<Sound>(soundOrMusic)) {
		StopSound(get<Sound>(soundOrMusic));
		ret = true;
	}
	else if (holds_alternative<Music>(soundOrMusic)) {
		StopMusicStream(get<Music>(soundOrMusic));
		ret = true;
	}
	return ret;
}

bool RaylibAudioClip::IsPlaying() const noexcept {
	bool ret(false);
	if (holds_alternative<Sound>(soundOrMusic)) {
		ret = IsSoundPlaying(get<Sound>(soundOrMusic));
	}
	else if (holds_alternative<Music>(soundOrMusic)) {
		ret = IsMusicStreamPlaying(get<Music>(soundOrMusic));
	}
	return ret;
}

bool RaylibAudioClip::IsMusic() const noexcept {
	return holds_alternative<Music>(soundOrMusic);
}

void RaylibAudioClip::Update() noexcept {
	if (holds_alternative<Music>(soundOrMusic)) {
		UpdateMusicStream(get<Music>(soundOrMusic));
	}
}
