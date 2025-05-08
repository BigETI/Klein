#pragma once

#include <filesystem>

#include "../Exportables/Exportable.hxx"

namespace Klein::Audio {
	class IAudioClip {
	public:

		virtual ~IAudioClip() noexcept {
			// ...
		}
		
		virtual bool Play() noexcept = 0;
		virtual bool Stop() noexcept = 0;
		virtual bool IsPlaying() const noexcept = 0;
		virtual bool IsMusic() const noexcept = 0;
		virtual void Update() noexcept = 0;
	};
}
