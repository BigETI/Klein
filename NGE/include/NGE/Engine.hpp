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

namespace NGE::SceneManagement {
	class Node;
}

namespace NGE {
	class Engine {
	public:

		NGE::EventSystem::Event<std::chrono::high_resolution_clock::time_point> OnGameStarted;
		NGE::EventSystem::Event<std::chrono::high_resolution_clock::duration> OnFrameRendered;
		NGE::EventSystem::Event<std::chrono::high_resolution_clock::duration> OnGameTicked;
		NGE::EventSystem::Event<int> OnGameStopped;

		NGE_API Engine(const std::span<const std::string> commandLineArguments);
		NGE_API Engine(const std::span<const std::string> commandLineArguments, const std::filesystem::path& configurationFilePath);

		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;

		NGE_API ~Engine();

		NGE_API bool IsGameRunning() const noexcept;
		NGE_API std::chrono::high_resolution_clock::time_point GetGameStartTimePoint() const noexcept;
		NGE_API const std::vector<NGE::InputSystem::InputEvent>& GetCurrentInputEvents() const noexcept;
		NGE_API std::vector<NGE::InputSystem::InputEvent>& GetCurrentInputEvents(
			std::vector<NGE::InputSystem::InputEvent>& result
		) const;
		NGE_API const std::vector<std::shared_ptr<NGE::SceneManagement::Node>>& GetScenes() const noexcept;
		NGE_API std::vector<std::shared_ptr<NGE::SceneManagement::Node>>& GetScenes(
			std::vector<std::shared_ptr<NGE::SceneManagement::Node>>& result
		) const;
		NGE_API const std::vector<NGE::Rendering::RenderingContext>& GetRenderingContexts() const noexcept;
		NGE_API std::vector<NGE::Rendering::RenderingContext>& GetRenderingContexts() noexcept;
		NGE_API int GetExitCode();
		NGE_API int Start();
		NGE_API void Stop();
		NGE_API void Stop(int exitCode);

		NGE_API std::shared_ptr<NGE::SceneManagement::Node> CreateNewEmptyScene();
		template <typename TNode>
		constexpr inline std::shared_ptr<TNode> CreateNewScene() {
			std::shared_ptr<TNode> ret(std::make_shared<TNode>(TNode::NullParent));
			scenes.push_back(ret);
			return ret;
		}
		NGE_API bool RemoveScene(const std::shared_ptr<NGE::SceneManagement::Node>& scene);
		NGE_API void ClearScenes();

		NGE_API bool AddRenderer(const std::shared_ptr<NGE::Rendering::IRenderer>& renderer);
		NGE_API bool RemoveRenderer(const std::shared_ptr<NGE::Rendering::IRenderer>& renderer);
		NGE_API void ClearRenderers() noexcept;
		
		NGE_API bool AddInputHandler(const std::shared_ptr<NGE::InputSystem::IInputHandler>& inputHandler);
		NGE_API bool RemoveInputHandler(const std::shared_ptr<NGE::InputSystem::IInputHandler>& inputHandler);
		NGE_API void ClearInputHandlers() noexcept;
		
		Engine& operator =(const Engine&) = delete;
		Engine& operator =(Engine&&) = delete;

	private:

		NGE::Math::Ratio<unsigned int> targetGameTickRate;
		NGE::Math::Ratio<unsigned int> targetFrameRate;
		std::atomic_bool isGameRunning;
		std::chrono::high_resolution_clock::time_point gameStartTimePoint;
		std::vector<NGE::InputSystem::InputEvent> currentInputEvents;
		std::vector<std::shared_ptr<NGE::SceneManagement::Node>> scenes;
		std::vector<NGE::Rendering::RenderingContext> renderingContexts;
		std::vector<std::shared_ptr<NGE::Rendering::IRenderer>> renderers;
		std::vector<std::shared_ptr<NGE::InputSystem::IInputHandler>> inputHandlers;
		std::atomic_int exitCode;
	};
}
