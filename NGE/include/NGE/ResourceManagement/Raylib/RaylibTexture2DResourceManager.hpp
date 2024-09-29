#pragma once

#include <string>

#include <raylib.h>

#include "../../Exportables/Exportable.hxx"
#include "../AResourceManager.hpp"
#include "../ResourceID.hpp"

namespace NGE::ResourceManagement::Raylib {
	class RaylibTexture2DResourceManager : public NGE::ResourceManagement::AResourceManager<Texture2D> {
	public:

		NGE_API RaylibTexture2DResourceManager();
		NGE_API virtual ~RaylibTexture2DResourceManager();

		NGE_API void Initialize();
		NGE_API void Deinitialize();

	protected:

		NGE_API virtual bool TryLoadingResource(const ResourceID& resourceID, Texture2D& result) override;
		NGE_API virtual void UnloadResource(const Texture2D& resource) override;

	private:

		Texture2D invalidTexture2D;
	};
}
