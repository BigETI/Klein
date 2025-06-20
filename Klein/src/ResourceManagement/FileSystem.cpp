#include <filesystem>

#include <Klein/ResourceManagement/FileSystem.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std::filesystem;

using namespace Klein::ResourceManagement;

const path& FileSystem::GetExecutableDirectoryPath() noexcept {
	return executableDirectoryPath;
}

void FileSystem::SetExecutableDirectoryPath(const path& executableDirectoryPath) {
	FileSystem::executableDirectoryPath = executableDirectoryPath;
}

path FileSystem::GetFilePathFromResourceID(const ResourceID& resourceID) {
	return executableDirectoryPath / "Resources" / resourceID.GetString();
}

path& FileSystem::GetFilePathFromResourceID(const ResourceID& resourceID, path& result) {
	return result = GetFilePathFromResourceID(resourceID);
}

path FileSystem::executableDirectoryPath(current_path());
