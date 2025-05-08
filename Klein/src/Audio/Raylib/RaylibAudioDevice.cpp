#include <filesystem>
#include <memory>

#include <raylib.h>

#include <Klein/Audio/IAudioClip.hpp>
#include <Klein/Audio/Raylib/RaylibAudioClip.hpp>
#include <Klein/Audio/Raylib/RaylibAudioDevice.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace Klein::Audio;
using namespace Klein::Audio::Raylib;
using namespace Klein::ResourceManagement;

RaylibAudioDevice::RaylibAudioDevice() {
	InitAudioDevice();
}

RaylibAudioDevice::~RaylibAudioDevice() noexcept {
	CloseAudioDevice();
}

shared_ptr<IAudioClip> RaylibAudioDevice::LoadAudioClip(const ResourceID& resourceID, bool isMusic) noexcept {
	return RaylibAudioClip::Load(resourceID, isMusic);
}
