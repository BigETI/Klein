#include <memory>
#include <variant>

#include <raylib.h>

#include <Klein/Audio/Raylib/RaylibAudioClip.hpp>

using namespace std;

using namespace Klein::Audio::Raylib;

RaylibAudioClip::RaylibAudioClip(const shared_ptr<Sound>& sound) : soundOrMusic(sound), volume(1.0f) {
	// ...
}

RaylibAudioClip::RaylibAudioClip(const shared_ptr<Music>& music) : soundOrMusic(music), volume(1.0f) {
	// ...
}

RaylibAudioClip::~RaylibAudioClip() noexcept {
	Stop();
	if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		UnloadMusicStream(*get<shared_ptr<Music>>(soundOrMusic));
	}
}

bool RaylibAudioClip::Play(float volume) noexcept {
	bool ret(false);
	if (holds_alternative<shared_ptr<Sound>>(soundOrMusic)) {
		Sound& sound(*get<shared_ptr<Sound>>(soundOrMusic));
		PlaySound(sound);
		SetSoundVolume(sound, volume);
		this->volume = volume;
		ret = true;
	}
	else if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		Music& music(*get<shared_ptr<Music>>(soundOrMusic));
		PlayMusicStream(music);
		SetMusicVolume(music, volume);
		this->volume = volume;
		ret = true;
	}
	return ret;
}

bool RaylibAudioClip::Stop() noexcept {
	bool ret(false);
	if (holds_alternative<shared_ptr<Sound>>(soundOrMusic)) {
		StopSound(*get<shared_ptr<Sound>>(soundOrMusic));
		ret = true;
	}
	else if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		StopMusicStream(*get<shared_ptr<Music>>(soundOrMusic));
		ret = true;
	}
	return ret;
}

bool RaylibAudioClip::IsPlaying() const noexcept {
	bool ret(false);
	if (holds_alternative<shared_ptr<Sound>>(soundOrMusic)) {
		ret = IsSoundPlaying(*get<shared_ptr<Sound>>(soundOrMusic));
	}
	else if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		ret = IsMusicStreamPlaying(*get<shared_ptr<Music>>(soundOrMusic));
	}
	return ret;
}

bool RaylibAudioClip::IsMusic() const noexcept {
	return holds_alternative<shared_ptr<Music>>(soundOrMusic);
}

float RaylibAudioClip::GetVolume() const noexcept {
	return volume;
}

bool RaylibAudioClip::SetVolume(float volume) noexcept {
	bool ret(false);
	if (holds_alternative<shared_ptr<Sound>>(soundOrMusic)) {
		SetSoundVolume(*get<shared_ptr<Sound>>(soundOrMusic), volume);
		this->volume = volume;
		ret = true;
	}
	else if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		SetMusicVolume(*get<shared_ptr<Music>>(soundOrMusic), volume);
		this->volume = volume;
		ret = true;
	}
	return ret;
}

void RaylibAudioClip::Update() noexcept {
	if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		Music& music(*get<shared_ptr<Music>>(soundOrMusic));
		if (IsMusicStreamPlaying(music)) {
			UpdateMusicStream(music);
		}
	}
}
