#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

#include <iostream>

#include "ResourceID.hpp"

namespace NGE::ResourceManagement {
	template <typename TResource>
	class AResourceManager {
	public:

		AResourceManager() {
			// ...
		}

		AResourceManager(const AResourceManager<TResource>&) = delete;
		AResourceManager(AResourceManager<TResource>&&) noexcept = delete;

		virtual ~AResourceManager() {
			Clear();
		}

		bool TryGettingResource(const ResourceID& resourceID, TResource& result) {
			bool ret(false);
			const auto& it(loadedResources.find(resourceID.GetHash()));
			if (it == loadedResources.end()) {
				ret = TryLoadingResource(resourceID, result);
				if (ret) {
					loadedResources.insert_or_assign(resourceID.GetHash(), result);
					//std::cout << "Successfully loaded resource \"" << resourceID.GetString() << "\", with hash " << resourceID.GetHash() << std::endl;
				}
				/*else {
					std::cerr << "Failed to load resource \"" << resourceID.GetString() << "\" with hash " << resourceID.GetHash() << std::endl;
				}*/
			}
			else {
				result = it->second;
				ret = true;
			}
			return ret;
		}

		bool RemoveResource(const ResourceID& resourceID) {
			const auto& it(loadedResources.find(resourceID.GetHash()));
			bool ret(it != loadedResources.end());
			if (ret) {
				UnloadResource(it->second);
				loadedResources.erase(it);
			}
			return ret;
		}

		void Clear() {
			for (const auto& loaded_resource : loadedResources) {
				UnloadResource(loaded_resource.second);
			}
			loadedResources.clear();
		}

		AResourceManager& operator =(const AResourceManager&) = delete;
		AResourceManager& operator =(AResourceManager&&) noexcept = delete;

	protected:

		virtual bool TryLoadingResource(const ResourceID& resourceID, TResource& result) = 0;
		virtual void UnloadResource(const TResource& resource) = 0;

	private:

		std::unordered_map<std::size_t, TResource> loadedResources;
	};
}
