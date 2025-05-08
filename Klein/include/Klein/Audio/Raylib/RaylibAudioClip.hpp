#pragma once

#include <memory>
#include <string>
#include <variant>

#include <raylib.h>

#include "../../Exportables/Exportable.hxx"
#include "../../ResourceManagement/ResourceID.hpp"
#include "../IAudioClip.hpp"
#include "RaylibAudioClip.hpp"

namespace Klein::Audio::Raylib {
	class RaylibAudioClip : public Klein::Audio::IAudioClip {
	public:

		RaylibAudioClip() = delete;

		KLEIN_API RaylibAudioClip(const std::shared_ptr<Sound>& sound);
		KLEIN_API RaylibAudioClip(const std::shared_ptr<Music>& music);

		KLEIN_API virtual ~RaylibAudioClip() noexcept override;

		KLEIN_API virtual bool Play() noexcept override;
		KLEIN_API virtual bool Stop() noexcept override;
		KLEIN_API virtual bool IsPlaying() const noexcept override;
		KLEIN_API virtual bool IsMusic() const noexcept override;
		KLEIN_API virtual void Update() noexcept override;

	private:

		std::variant<std::shared_ptr<Sound>, std::shared_ptr<Music>> soundOrMusic;
	};
}
