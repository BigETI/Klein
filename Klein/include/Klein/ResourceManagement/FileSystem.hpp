#pragma once

#include <filesystem>
#include <string>

#include "../Exportables/Exportable.hxx"
#include "ResourceID.hpp"

namespace Klein::ResourceManagement {
	class FileSystem {
	public:

		FileSystem() = delete;
		FileSystem(const FileSystem&) = delete;
		FileSystem(FileSystem&&) noexcept = delete;
		~FileSystem() = delete;

		KLEIN_API static const std::filesystem::path& GetExecutableDirectoryPath() noexcept;
		KLEIN_API static void SetExecutableDirectoryPath(const std::filesystem::path& executableDirectoryPath);
		KLEIN_API static std::filesystem::path GetFilePathFromResourceID(const ResourceID& resourceID);
		KLEIN_API static std::filesystem::path& GetFilePathFromResourceID(const ResourceID& resourceID, std::filesystem::path& result);

		FileSystem& operator =(const FileSystem&) = delete;
		FileSystem& operator =(FileSystem&&) noexcept = delete;

	private:

		static std::filesystem::path executableDirectoryPath;
	};
}
