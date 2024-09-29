#include <filesystem>

#include <NGE/ResourceManagement/FileSystem.hpp>
#include <NGE/ResourceManagement/ResourceID.hpp>

using namespace std;
using namespace std::filesystem;

using namespace NGE::ResourceManagement;

path& FileSystem::GetFilePathFromResourceID(const ResourceID& resourceID, path& result) {
	return result = std::filesystem::current_path() / "Resources" / resourceID.GetString();
}
