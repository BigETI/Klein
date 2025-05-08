#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include <raylib.h>

#include <Klein/ResourceManagement/FileSystem.hpp>
#include <Klein/ResourceManagement/Raylib/RaylibSoundResourceManager.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace Klein::ResourceManagement;
using namespace Klein::ResourceManagement::Raylib;

RaylibSoundResourceManager::RaylibSoundResourceManager() : AResourceManager<Sound>() {
	// ...
}

RaylibSoundResourceManager::~RaylibSoundResourceManager() noexcept {
	Clear();
}

bool RaylibSoundResourceManager::TryLoadingResource(const ResourceID& resourceID, shared_ptr<Sound>& result) noexcept {
	bool ret(false);
	path resource_file_path;
	if (!resourceID.GetString().empty() && exists(FileSystem::GetFilePathFromResourceID(resourceID, resource_file_path))) {
		string resource_file_path_string(resource_file_path.generic_string());
		Sound sound(LoadSound(resource_file_path_string.c_str()));
		if (IsSoundValid(sound)) {
			result = make_shared<Sound>(sound);
			ret = true;
		}
	}
	if (!ret) {
		cerr << "Failed to load sound \"" << resourceID.GetString() << "\" with hash " << resourceID.GetHash() << endl;
	}
	return ret;
}

void RaylibSoundResourceManager::UnloadResource(const shared_ptr<Sound>& resource) noexcept {
	if (resource && IsSoundValid(*resource)) {
		UnloadSound(*resource);
	}
}
