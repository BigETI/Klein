#include <filesystem>

#include <Klein/ResourceManagement/FileSystem.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace Klein::ResourceManagement;

path& FileSystem::GetFilePathFromResourceID(const ResourceID& resourceID, path& result) {
	return result = std::filesystem::current_path() / "Resources" / resourceID.GetString();
}
