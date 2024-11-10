#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <span>
#include <string>

#include "EventSystem/Event.hpp"
#include "Exportables/Exportable.hxx"
#include "InputSystem/IInputHandler.hpp"
#include "Math/Ratio.hpp"
#include "Rendering/IRenderer.hpp"
#include "Rendering/RenderingContext.hpp"
#include "SceneManagement/Node.hpp"

namespace Klein::SceneManagement {
	class Node;
}

namespace Klein {
	class Engine {
	public:

		Klein::EventSystem::Event<std::chrono::high_resolution_clock::time_point> OnGameStarted;
		Klein::EventSystem::Event<std::chrono::high_resolution_clock::duration> OnFrameRendered;
		Klein::EventSystem::Event<std::chrono::high_resolution_clock::duration> OnGameTicked;
		Klein::EventSystem::Event<int> OnGameStopped;

		KLEIN_API Engine(const std::span<const std::string> commandLineArguments);
		KLEIN_API Engine(const std::span<const std::string> commandLineArguments, const std::filesystem::path& configurationFilePath);

		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		KLEIN_API ~Engine();

		KLEIN_API bool IsGameRunning() const noexcept;
		KLEIN_API std::chrono::high_resolution_clock::time_point GetGameStartTimePoint() const noexcept;
		KLEIN_API const std::vector<Klein::InputSystem::InputEvent>& GetCurrentInputEvents() const noexcept;
		KLEIN_API std::vector<Klein::InputSystem::InputEvent>& GetCurrentInputEvents(
			std::vector<Klein::InputSystem::InputEvent>& result
		) const;
		KLEIN_API const std::vector<std::shared_ptr<Klein::SceneManagement::Node>>& GetScenes() const noexcept;
		KLEIN_API std::vector<std::shared_ptr<Klein::SceneManagement::Node>>& GetScenes(
			std::vector<std::shared_ptr<Klein::SceneManagement::Node>>& result
		) const;
		KLEIN_API const std::vector<Klein::Rendering::RenderingContext>& GetRenderingContexts() const noexcept;
		KLEIN_API std::vector<Klein::Rendering::RenderingContext>& GetRenderingContexts() noexcept;
		KLEIN_API int GetExitCode();
		KLEIN_API int Start();
		KLEIN_API void Stop();
		KLEIN_API void Stop(int exitCode);

		KLEIN_API std::shared_ptr<Klein::SceneManagement::Node> CreateNewEmptyScene();
		template <typename TNode>
		constexpr inline std::shared_ptr<TNode> CreateNewScene() {
			std::shared_ptr<TNode> ret(std::make_shared<TNode>(TNode::NullParent));
			scenes.push_back(ret);
			return ret;
		}
		KLEIN_API bool RemoveScene(const std::shared_ptr<Klein::SceneManagement::Node>& scene);
		KLEIN_API void ClearScenes();

		KLEIN_API bool AddRenderer(const std::shared_ptr<Klein::Rendering::IRenderer>& renderer);
		KLEIN_API bool RemoveRenderer(const std::shared_ptr<Klein::Rendering::IRenderer>& renderer);
		KLEIN_API void ClearRenderers() noexcept;

		KLEIN_API bool AddInputHandler(const std::shared_ptr<Klein::InputSystem::IInputHandler>& inputHandler);
		KLEIN_API bool RemoveInputHandler(const std::shared_ptr<Klein::InputSystem::IInputHandler>& inputHandler);
		KLEIN_API void ClearInputHandlers() noexcept;

		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

	private:

		Klein::Math::Ratio<unsigned int> targetGameTickRate;
		Klein::Math::Ratio<unsigned int> targetFrameRate;
		std::atomic_bool isGameRunning;
		std::chrono::high_resolution_clock::time_point gameStartTimePoint;
		std::vector<Klein::InputSystem::InputEvent> currentInputEvents;
		std::vector<std::shared_ptr<Klein::SceneManagement::Node>> scenes;
		std::vector<Klein::Rendering::RenderingContext> renderingContexts;
		std::vector<std::shared_ptr<Klein::Rendering::IRenderer>> renderers;
		std::vector<std::shared_ptr<Klein::InputSystem::IInputHandler>> inputHandlers;
		std::atomic_int exitCode;
	};
}
