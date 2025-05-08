#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include <raylib.h>

#include <Klein/ResourceManagement/FileSystem.hpp>
#include <Klein/ResourceManagement/Raylib/RaylibTexture2DResourceManager.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace Klein::ResourceManagement::Raylib;

RaylibTexture2DResourceManager::RaylibTexture2DResourceManager() : AResourceManager<Texture2D>(), invalidTexture2D(make_shared<Texture2D>(Texture2D({ 0 }))) {
	// ...
}

RaylibTexture2DResourceManager::~RaylibTexture2DResourceManager() noexcept {
	Clear();
}

void RaylibTexture2DResourceManager::Initialize() noexcept {
	if (IsWindowReady() && !IsTextureValid(*invalidTexture2D)) {
		Image empty_image(GenImageChecked(4, 4, 1, 1, { 0xFF, 0x00, 0xFF, 0xFF }, { 0x00, 0xFF, 0x00, 0xFF }));
		*invalidTexture2D = LoadTextureFromImage(empty_image);
		UnloadImage(empty_image);
	}
}

void RaylibTexture2DResourceManager::Deinitialize() noexcept {
	Clear();
	if (IsWindowReady() && IsTextureValid(*invalidTexture2D)) {
		UnloadTexture(*invalidTexture2D);
	}
}

bool RaylibTexture2DResourceManager::TryLoadingResource(const ResourceID& resourceID, shared_ptr<Texture2D>& result) noexcept {
	bool ret(false);
	path resource_file_path;
	if (!resourceID.GetString().empty() && exists(FileSystem::GetFilePathFromResourceID(resourceID, resource_file_path))) {
		string resource_file_path_string(resource_file_path.generic_string());
		Texture2D texture_2d(LoadTexture(resource_file_path_string.c_str()));
		if (IsTextureValid(texture_2d)) {
			result = make_shared<Texture2D>(texture_2d);
			ret = true;
		}
	}
	if (!ret && IsTextureValid(*invalidTexture2D)) {
		if (IsTextureValid(*invalidTexture2D)) {
			result = invalidTexture2D;
			ret = true;
		}
		cerr << "Failed to load texture \"" << resourceID.GetString() << "\" with hash " << resourceID.GetHash() << endl;
	}
	return ret;
}

void RaylibTexture2DResourceManager::UnloadResource(const shared_ptr<Texture2D>& resource) noexcept {
	if (resource && (resource != invalidTexture2D) && IsWindowReady() && IsTextureValid(*resource)) {
		UnloadTexture(*resource);
	}
}
