#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

#include "ResourceID.hpp"

namespace Klein::ResourceManagement {
	template <typename TResource>
	class AResourceManager {
	public:

		AResourceManager() {
			// ...
		}

		AResourceManager(const AResourceManager<TResource>&) = delete;
		AResourceManager(AResourceManager<TResource>&&) noexcept = delete;

		virtual ~AResourceManager() noexcept {
			// ...
		}

		bool TryGettingResource(const ResourceID& resourceID, std::shared_ptr<TResource>& result) noexcept {
			bool ret(false);
			const auto& it(loadedResources.find(resourceID.GetHash()));
			if (it == loadedResources.end()) {
				ret = TryLoadingResource(resourceID, result);
				if (ret) {
					loadedResources.insert_or_assign(resourceID.GetHash(), result);
				}
			}
			else {
				result = it->second;
				ret = true;
			}
			return ret;
		}

		bool RemoveResource(const ResourceID& resourceID) noexcept {
			const auto& it(loadedResources.find(resourceID.GetHash()));
			bool ret(it != loadedResources.end());
			if (ret) {
				UnloadResource(it->second);
				loadedResources.erase(it);
			}
			return ret;
		}

		void Clear() noexcept {
			for (auto& loaded_resource : loadedResources) {
				UnloadResource(loaded_resource.second);
			}
			loadedResources.clear();
		}

		AResourceManager& operator =(const AResourceManager&) = delete;
		AResourceManager& operator =(AResourceManager&&) noexcept = delete;

	protected:

		virtual bool TryLoadingResource(const ResourceID& resourceID, std::shared_ptr<TResource>& result) noexcept = 0;
		virtual void UnloadResource(const std::shared_ptr<TResource>& resource) noexcept = 0;

	private:

		std::unordered_map<std::size_t, std::shared_ptr<TResource>> loadedResources;
	};
}
