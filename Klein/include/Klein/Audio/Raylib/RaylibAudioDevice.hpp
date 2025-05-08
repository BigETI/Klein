#pragma once

#include <filesystem>
#include <memory>

#include "../../Exportables/Exportable.hxx"
#include "../../ResourceManagement/ResourceID.hpp"
#include "../IAudioClip.hpp"
#include "../IAudioDevice.hpp"

namespace Klein::Audio::Raylib {
	class RaylibAudioDevice : public Klein::Audio::IAudioDevice {
	public:

		KLEIN_API RaylibAudioDevice();

		RaylibAudioDevice(const RaylibAudioDevice&) = delete;
		RaylibAudioDevice(RaylibAudioDevice&&) = delete;

		KLEIN_API virtual ~RaylibAudioDevice() noexcept override;

		KLEIN_API virtual std::shared_ptr<Klein::Audio::IAudioClip> LoadAudioClip(const Klein::ResourceManagement::ResourceID& resourceID, bool isMusic) noexcept override;

		RaylibAudioDevice& operator=(const RaylibAudioDevice&) = delete;
		RaylibAudioDevice& operator=(RaylibAudioDevice&&) = delete;
	};
}
