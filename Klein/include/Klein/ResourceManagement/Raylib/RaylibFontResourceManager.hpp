#pragma once

#include <string>

#include <raylib.h>

#include "../../Exportables/Exportable.hxx"
#include "../AResourceManager.hpp"
#include "../ResourceID.hpp"

namespace Klein::ResourceManagement::Raylib {
	class RaylibFontResourceManager : public Klein::ResourceManagement::AResourceManager<Font> {
	public:

		KLEIN_API RaylibFontResourceManager();
		KLEIN_API virtual ~RaylibFontResourceManager() noexcept override;

		KLEIN_API void Initialize() noexcept;
		KLEIN_API void Deinitialize() noexcept;

	protected:

		KLEIN_API virtual bool TryLoadingResource(const Klein::ResourceManagement::ResourceID& resourceID, std::shared_ptr<Font>& result) noexcept override;
		KLEIN_API virtual void UnloadResource(const std::shared_ptr<Font>& resource) noexcept override;
	};
}
