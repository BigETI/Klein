#pragma once

#include <chrono>
#include <filesystem>
#include <memory>

#include "../../Audio/IAudioClip.hpp"
#include "../../Audio/IAudioDevice.hpp"
#include "../../Engine.hpp"
#include "../../Exportables/Exportable.hxx"
#include "../../ResourceManagement/ResourceID.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"

namespace Klein::Scripting::Audio {
	class AudioPlayerScript : public Klein::Scripting::Script {
	public:

		KLEIN_API AudioPlayerScript(Klein::SceneManagement::Node* node);
		KLEIN_API virtual ~AudioPlayerScript() noexcept;

		KLEIN_API const Klein::ResourceManagement::ResourceID& GetResourceID() const noexcept;
		KLEIN_API void SetResourceID(const Klein::ResourceManagement::ResourceID& resourceID, bool isMusic, bool isUsingCache = true) noexcept;
		KLEIN_API void SetResourceID(Klein::ResourceManagement::ResourceID&& resourceID, bool isMusic, bool isUsingCache = true) noexcept;
		KLEIN_API bool IsMusic() const noexcept;
		KLEIN_API bool Preload() noexcept;
		KLEIN_API void PreloadWhenAvailable() noexcept;
		KLEIN_API bool Play(float volume = 1.0f) noexcept;
		KLEIN_API void PlayWhenAvailable(float volume = 1.0f) noexcept;
		KLEIN_API bool Stop() noexcept;
		KLEIN_API bool IsPlaying() const noexcept;

	protected:

		KLEIN_API virtual void OnEnable(Klein::Engine& engine) override;
		KLEIN_API virtual void OnDisable(Klein::Engine& engine) override;
		KLEIN_API virtual void OnGameTick(Klein::Engine& engine, const std::chrono::high_resolution_clock::duration& deltaTime) override;

	private:

		Klein::Engine* engine;
		Klein::ResourceManagement::ResourceID resourceID;
		bool isMusic;
		bool isUsingCache;
		float volume;
		bool isPreloadingWhenAvailable;
		bool isEnqueuedForPlayback;
		std::weak_ptr<Klein::Audio::IAudioDevice> lastAudioDevice;
		std::shared_ptr<Klein::Audio::IAudioClip> lastAudioClip;
	};
}
