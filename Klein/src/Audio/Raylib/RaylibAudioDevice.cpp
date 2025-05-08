#include <filesystem>
#include <cstring>
#include <iostream>
#include <memory>

#include <raylib.h>

#include <Klein/Audio/IAudioClip.hpp>
#include <Klein/Audio/Raylib/RaylibAudioClip.hpp>
#include <Klein/Audio/Raylib/RaylibAudioDevice.hpp>
#include <Klein/ResourceManagement/FileSystem.hpp>
#include <Klein/ResourceManagement/Raylib/RaylibSoundResourceManager.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace Klein::Audio;
using namespace Klein::Audio::Raylib;
using namespace Klein::ResourceManagement;
using namespace Klein::ResourceManagement::Raylib;

RaylibSoundResourceManager RaylibAudioDevice::raylibSoundResourceManager;

RaylibAudioDevice::RaylibAudioDevice() {
	InitAudioDevice();
}

RaylibAudioDevice::~RaylibAudioDevice() noexcept {
	CloseAudioDevice();
}

shared_ptr<IAudioClip> RaylibAudioDevice::LoadAudioClip(const ResourceID& resourceID, bool isMusic) noexcept {
	shared_ptr<IAudioClip> ret;
	if (IsAudioDeviceReady()) {
		if (isMusic) {
			path path;
			Music music(LoadMusicStream(FileSystem::GetFilePathFromResourceID(resourceID, path).string().c_str()));
			if (IsMusicValid(music)) {
				ret = make_shared<RaylibAudioClip>(make_shared<Music>(music));
			}
		}
		else {
			shared_ptr<Sound> sound;
			if (raylibSoundResourceManager.TryGettingResource(resourceID, sound)) {
				ret = make_shared<RaylibAudioClip>(sound);
			}
		}
	}
	if (!ret) {
		cerr << "Failed to load audio clip with resource ID \"" << resourceID.GetString() << "\"" << " (" << resourceID.GetHash() << ")" << endl;
	}
	return ret;
}
