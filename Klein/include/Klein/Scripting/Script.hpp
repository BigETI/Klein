#pragma once

#include <chrono>
#include <memory>

#include "../EventSystem/Event.hpp"
#include "../Exportables/Exportable.hxx"
#include "../Engine.hpp"
#include "../SceneManagement/Node.hpp"

namespace Klein {
	class Engine;
}

namespace Klein::SceneManagement {
	class Node;
}

namespace Klein::Scripting {
	class Script {
	public:

		Klein::EventSystem::Event<Klein::Engine&> OnInitialized;
		Klein::EventSystem::Event<Klein::Engine&> OnDeinitialized;
		Klein::EventSystem::Event<Klein::Engine&> OnEnabled;
		Klein::EventSystem::Event<Klein::Engine&> OnDisabled;
		Klein::EventSystem::Event<Klein::Engine&, std::chrono::high_resolution_clock::duration> OnGameTicked;
		Klein::EventSystem::Event<Klein::Engine&, std::chrono::high_resolution_clock::duration> OnBeforeFrameRendered;
		Klein::EventSystem::Event<Klein::Engine&, std::chrono::high_resolution_clock::duration> OnFrameRendered;

		KLEIN_API Script(Klein::SceneManagement::Node* node);

		Script(const Script&) = delete;
		Script(Script&&) = delete;

		KLEIN_API virtual ~Script() noexcept;

		KLEIN_API bool IsInitialized() const noexcept;
		KLEIN_API bool IsEnabled() const noexcept;
		KLEIN_API void SetEnabledState(bool enabledState) noexcept;
		KLEIN_API const Klein::SceneManagement::Node& GetNode() const noexcept;
		KLEIN_API Klein::SceneManagement::Node& GetNode() noexcept;
		KLEIN_API void InitializeOrGameTick(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		KLEIN_API void InitializeOrBeforeFrameRender(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		KLEIN_API void InitializeOrFrameRender(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		KLEIN_API void Deinitialize();
		KLEIN_API void Enable();
		KLEIN_API void Disable();

		Script& operator =(const Script&) = delete;
		Script& operator =(Script&&) = delete;

	protected:

		KLEIN_API virtual void OnInitialize(Klein::Engine& engine);
		KLEIN_API virtual void OnDeinitialize(Klein::Engine& engine);
		KLEIN_API virtual void OnEnable(Klein::Engine& engine);
		KLEIN_API virtual void OnDisable(Klein::Engine& engine);
		KLEIN_API virtual void OnGameTick(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		KLEIN_API virtual void OnBeforeFrameRender(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		KLEIN_API virtual void OnFrameRender(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);

	private:

		bool isInitialized;
		bool isEnabled;
		Klein::SceneManagement::Node* node;
		Klein::Engine* engine;
	};
}
