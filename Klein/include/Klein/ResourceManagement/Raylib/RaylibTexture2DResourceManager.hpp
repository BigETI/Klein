#pragma once

#include <memory>
#include <string>

#include <raylib.h>

#include "../../Exportables/Exportable.hxx"
#include "../AResourceManager.hpp"
#include "../ResourceID.hpp"

namespace Klein::ResourceManagement::Raylib {
	class RaylibTexture2DResourceManager : public Klein::ResourceManagement::AResourceManager<Texture2D> {
	public:

		KLEIN_API RaylibTexture2DResourceManager();
		KLEIN_API virtual ~RaylibTexture2DResourceManager() noexcept override;

		KLEIN_API void Initialize() noexcept;
		KLEIN_API void Deinitialize() noexcept;

	protected:

		KLEIN_API virtual bool TryLoadingResource(const Klein::ResourceManagement::ResourceID& resourceID, std::shared_ptr<Texture2D>& result) noexcept override;
		KLEIN_API virtual void UnloadResource(const std::shared_ptr<Texture2D>& resource) noexcept override;

	private:

		std::shared_ptr<Texture2D> invalidTexture2D;
	};
}
