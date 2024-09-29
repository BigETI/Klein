#pragma once

#include <filesystem>
#include <string>

#include "../Exportables/Exportable.hxx"
#include "ResourceID.hpp"

namespace NGE::ResourceManagement {
	class FileSystem {
	public:

		FileSystem() = delete;
		FileSystem(const FileSystem&) = delete;
		FileSystem(FileSystem&&) noexcept = delete;
		~FileSystem() = delete;

		NGE_API static std::filesystem::path& GetFilePathFromResourceID(const ResourceID& resourceID, std::filesystem::path& result);

		FileSystem& operator =(const FileSystem&) = delete;
		FileSystem& operator =(FileSystem&&) noexcept = delete;
	};
}
