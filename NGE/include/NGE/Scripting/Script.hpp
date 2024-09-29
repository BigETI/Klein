#pragma once

#include <chrono>
#include <memory>

#include "../EventSystem/Event.hpp"
#include "../Exportables/Exportable.hxx"
#include "../Engine.hpp"
#include "../SceneManagement/Node.hpp"

namespace NGE {
	class Engine;
}

namespace NGE::SceneManagement {
	class Node;
}

namespace NGE::Scripting {
	class Script {
	public:

		NGE::EventSystem::Event<NGE::Engine&> OnInitialized;
		NGE::EventSystem::Event<NGE::Engine&> OnDeinitialized;
		NGE::EventSystem::Event<NGE::Engine&> OnEnabled;
		NGE::EventSystem::Event<NGE::Engine&> OnDisabled;
		NGE::EventSystem::Event<NGE::Engine&, std::chrono::high_resolution_clock::duration> OnGameTicked;
		NGE::EventSystem::Event<NGE::Engine&, std::chrono::high_resolution_clock::duration> OnBeforeFrameRendered;
		NGE::EventSystem::Event<NGE::Engine&, std::chrono::high_resolution_clock::duration> OnFrameRendered;

		NGE_API Script(NGE::SceneManagement::Node* node);

		Script(const Script&) = delete;
		Script(Script&&) = delete;

		NGE_API virtual ~Script() noexcept;

		NGE_API bool IsInitialized() const noexcept;
		NGE_API bool IsEnabled() const noexcept;
		NGE_API void SetEnabledState(bool enabledState) noexcept;
		NGE_API const NGE::SceneManagement::Node& GetNode() const noexcept;
		NGE_API NGE::SceneManagement::Node& GetNode() noexcept;
		NGE_API void InitializeOrGameTick(NGE::Engine& game, std::chrono::high_resolution_clock::duration deltaTime);
		NGE_API void InitializeOrBeforeFrameRender(NGE::Engine& game, std::chrono::high_resolution_clock::duration deltaTime);
		NGE_API void InitializeOrFrameRender(NGE::Engine& game, std::chrono::high_resolution_clock::duration deltaTime);
		NGE_API void Deinitialize();
		NGE_API void Enable();
		NGE_API void Disable();

		Script& operator =(const Script&) = delete;
		Script& operator =(Script&&) = delete;

	protected:

		NGE_API virtual void OnInitialize(NGE::Engine& game);
		NGE_API virtual void OnDeinitialize(NGE::Engine& game);
		NGE_API virtual void OnEnable(NGE::Engine& game);
		NGE_API virtual void OnDisable(NGE::Engine& game);
		NGE_API virtual void OnGameTick(NGE::Engine& game, std::chrono::high_resolution_clock::duration deltaTime);
		NGE_API virtual void OnBeforeFrameRender(NGE::Engine& game, std::chrono::high_resolution_clock::duration deltaTime);
		NGE_API virtual void OnFrameRender(NGE::Engine& game, std::chrono::high_resolution_clock::duration deltaTime);

	private:

		bool isInitialized;
		bool isEnabled;
		NGE::SceneManagement::Node* node;
		NGE::Engine* game;
	};
}
