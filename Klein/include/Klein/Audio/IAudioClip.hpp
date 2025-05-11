#pragma once

#include <filesystem>

#include "../Exportables/Exportable.hxx"

namespace Klein::Audio {
	class IAudioClip {
	public:

		virtual ~IAudioClip() noexcept {
			// ...
		}
		
		virtual bool Play(float volume = 1.0f) noexcept = 0;
		virtual bool Stop() noexcept = 0;
		virtual bool IsPlaying() const noexcept = 0;
		virtual bool IsMusic() const noexcept = 0;
		virtual float GetVolume() const noexcept = 0;
		virtual bool SetVolume(float volume) noexcept = 0;
		virtual void Update() noexcept = 0;
	};
}
