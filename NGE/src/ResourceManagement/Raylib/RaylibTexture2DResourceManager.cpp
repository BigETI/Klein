#include <filesystem>
#include <string>

#include <raylib.h>

#include <NGE/ResourceManagement/FileSystem.hpp>
#include <NGE/ResourceManagement/Raylib/RaylibTexture2DResourceManager.hpp>
#include <NGE/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace NGE::ResourceManagement::Raylib;

RaylibTexture2DResourceManager::RaylibTexture2DResourceManager() : AResourceManager<Texture2D>(), invalidTexture2D({0}) {
	// ...
}

RaylibTexture2DResourceManager::~RaylibTexture2DResourceManager() {
	// ...
}

void RaylibTexture2DResourceManager::Initialize() {
	if (IsWindowReady() && !IsTextureReady(invalidTexture2D)) {
		Image empty_image(GenImageChecked(4, 4, 1, 1, { 0xFF, 0x00, 0xFF, 0xFF }, { 0x00, 0xFF, 0x00, 0xFF }));
		invalidTexture2D = LoadTextureFromImage(empty_image);
		UnloadImage(empty_image);
	}
}

void RaylibTexture2DResourceManager::Deinitialize() {
	if (IsWindowReady() && IsTextureReady(invalidTexture2D)) {
		UnloadTexture(invalidTexture2D);
	}
	Clear();
}

bool RaylibTexture2DResourceManager::TryLoadingResource(const ResourceID& resourceID, Texture2D& result) {
	bool ret(false);
	path resource_file_path;
	if (!resourceID.GetString().empty() && exists(FileSystem::GetFilePathFromResourceID(resourceID, resource_file_path))) {
		string resource_file_path_string(resource_file_path.generic_string());
		result = LoadTexture(resource_file_path_string.c_str());
		ret = IsTextureReady(result);
	}
	if (!ret && IsTextureReady(invalidTexture2D)) {
		result = invalidTexture2D;
		ret = true;
		cerr << "Failed to load texture \"" << resourceID.GetString() << "\" with hash " << resourceID.GetHash() << endl;
	}
	return ret;
}

void RaylibTexture2DResourceManager::UnloadResource(const Texture2D& resource) {
	if (IsWindowReady() && IsTextureReady(resource)) {
		UnloadTexture(resource);
	}
}
