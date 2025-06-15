#pragma once

#include <filesystem>
#include <memory>

#include "../ResourceManagement/ResourceID.hpp"
#include "IAudioClip.hpp"

namespace Klein::Audio {
	class IAudioDevice {
	public:

		virtual ~IAudioDevice() noexcept {
			// ..
		}

		virtual std::shared_ptr<IAudioClip> LoadAudioClip(const Klein::ResourceManagement::ResourceID& resourceID, bool isMusic, bool isUsingCache = true) noexcept = 0;
	};
}
