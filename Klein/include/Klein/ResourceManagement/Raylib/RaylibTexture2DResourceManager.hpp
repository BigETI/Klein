#pragma once

#include <string>

#include <raylib.h>

#include "../../Exportables/Exportable.hxx"
#include "../AResourceManager.hpp"
#include "../ResourceID.hpp"

namespace Klein::ResourceManagement::Raylib {
	class RaylibTexture2DResourceManager : public Klein::ResourceManagement::AResourceManager<Texture2D> {
	public:

		KLEIN_API RaylibTexture2DResourceManager();
		KLEIN_API virtual ~RaylibTexture2DResourceManager();

		KLEIN_API void Initialize();
		KLEIN_API void Deinitialize();

	protected:

		KLEIN_API virtual bool TryLoadingResource(const ResourceID& resourceID, Texture2D& result) override;
		KLEIN_API virtual void UnloadResource(Texture2D& resource) override;

	private:

		Texture2D invalidTexture2D;
	};
}
