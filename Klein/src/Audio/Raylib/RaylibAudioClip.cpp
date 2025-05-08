#include <memory>
#include <variant>

#include <raylib.h>

#include <Klein/Audio/Raylib/RaylibAudioClip.hpp>

using namespace std;

using namespace Klein::Audio::Raylib;

RaylibAudioClip::RaylibAudioClip(const shared_ptr<Sound>& sound) : soundOrMusic(sound) {
	// ...
}

RaylibAudioClip::RaylibAudioClip(const shared_ptr<Music>& music) : soundOrMusic(music) {
	// ...
}

RaylibAudioClip::~RaylibAudioClip() noexcept {
	Stop();
	if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		UnloadMusicStream(*get<shared_ptr<Music>>(soundOrMusic));
	}
}

bool RaylibAudioClip::Play() noexcept {
	bool ret(false);
	if (holds_alternative<shared_ptr<Sound>>(soundOrMusic)) {
		PlaySound(*get<shared_ptr<Sound>>(soundOrMusic));
		ret = true;
	}
	else if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		PlayMusicStream(*get<shared_ptr<Music>>(soundOrMusic));
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

void RaylibAudioClip::Update() noexcept {
	if (holds_alternative<shared_ptr<Music>>(soundOrMusic)) {
		Music& music(*get<shared_ptr<Music>>(soundOrMusic));
		if (IsMusicStreamPlaying(music)) {
			UpdateMusicStream(music);
		}
	}
}
