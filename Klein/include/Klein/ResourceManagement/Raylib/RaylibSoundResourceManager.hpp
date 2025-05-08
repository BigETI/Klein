#pragma once

#include <string>

#include <raylib.h>

#include "../../Exportables/Exportable.hxx"
#include "../AResourceManager.hpp"
#include "../ResourceID.hpp"

namespace Klein::ResourceManagement::Raylib {
	class RaylibSoundResourceManager : public Klein::ResourceManagement::AResourceManager<Sound> {
	public:

		KLEIN_API RaylibSoundResourceManager();
		KLEIN_API virtual ~RaylibSoundResourceManager() noexcept override;

	protected:

		KLEIN_API virtual bool TryLoadingResource(const Klein::ResourceManagement::ResourceID& resourceID, std::shared_ptr<Sound>& result) noexcept override;
		KLEIN_API virtual void UnloadResource(const std::shared_ptr<Sound>& resource) noexcept override;
	};
}
