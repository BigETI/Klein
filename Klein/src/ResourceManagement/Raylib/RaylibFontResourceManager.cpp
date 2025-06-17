#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include <raylib.h>

#include <Klein/ResourceManagement/FileSystem.hpp>
#include <Klein/ResourceManagement/AResourceManager.hpp>
#include <Klein/ResourceManagement/Raylib/RaylibFontResourceManager.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace Klein::ResourceManagement;
using namespace Klein::ResourceManagement::Raylib;

RaylibFontResourceManager::RaylibFontResourceManager() : AResourceManager<Font>() {
	// ...
}

RaylibFontResourceManager::~RaylibFontResourceManager() noexcept {
	Clear();
}

bool RaylibFontResourceManager::TryLoadingResource(const ResourceID& resourceID, shared_ptr<Font>& result) noexcept {
	bool ret(false);
	path resource_file_path;
	if (!resourceID.GetString().empty() && exists(FileSystem::GetFilePathFromResourceID(resourceID, resource_file_path))) {
		string resource_file_path_string(resource_file_path.generic_string());
		Font font(LoadFont(resource_file_path_string.c_str()));
		if (IsFontValid(font)) {
			result = make_shared<Font>(font);
			ret = true;
		}
	}
	if (!ret) {
		Font font(GetFontDefault());
		if (IsFontValid(font)) {
			result = make_shared<Font>(font);
			ret = true;
		}
		cerr << "Failed to load font \"" << resourceID.GetString() << "\" with hash " << resourceID.GetHash() << endl;
	}
	return ret;
}

void RaylibFontResourceManager::UnloadResource(const shared_ptr<Font>& resource) noexcept {
	if (resource && IsFontValid(*resource)) {
		UnloadFont(*resource);
	}
}
