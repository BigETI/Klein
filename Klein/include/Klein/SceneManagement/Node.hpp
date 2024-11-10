#pragma once

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <memory>
#include <stack>
#include <string>
#include <type_traits>
#include <vector>

#include "../EventSystem/Event.hpp"
#include "../Exportables/Exportable.hxx"
#include "../Scripting/Script.hpp"
#include "../Engine.hpp"
#include "../Math/Vector2.hpp"

namespace Klein::Scripting {
	class Script;
}

namespace Klein {
	class Engine;
}

namespace Klein::SceneManagement {

	// TODO: Implement proper transformation matrices, and transformation operations
	class Node {
	public:

		static constexpr Node* NullParent = nullptr;
		Klein::EventSystem::Event<const std::shared_ptr<Node>&> OnChildAdded;
		Klein::EventSystem::Event<const std::shared_ptr<Node>&> OnChildRemoved;
		Klein::EventSystem::Event<const std::shared_ptr<Klein::Scripting::Script>&> OnScriptAdded;
		Klein::EventSystem::Event<const std::shared_ptr<Klein::Scripting::Script>&> OnScriptRemoved;

		KLEIN_API Node(Node* parent);
		KLEIN_API Node(Node* parent, const std::string& name);
		KLEIN_API Node(Node* parent, std::string&& name) noexcept;
		KLEIN_API ~Node();

		Node(const Node&) = delete;
		Node(Node&&) noexcept = delete;

		KLEIN_API Node* GetParent() const noexcept;
		KLEIN_API bool IsLocallyEnabled() const noexcept;
		KLEIN_API bool IsEnabled() const noexcept;
		KLEIN_API void Enable();
		KLEIN_API void Disable();
		KLEIN_API bool IsMarkedForDeletion() const noexcept;
		KLEIN_API const std::string& GetName() const noexcept;
		KLEIN_API std::string& GetName(std::string& result) const;
		KLEIN_API void SetName(const std::string& name);
		KLEIN_API void SetName(std::string&& name) noexcept;
		KLEIN_API const Klein::Math::Vector2<float>& GetLocalPosition() const noexcept;
		KLEIN_API void SetLocalPosition(const Klein::Math::Vector2<float>& localPosition) noexcept;
		KLEIN_API Klein::Math::Vector2<float> GetPosition() const noexcept;
		//KLEIN_API void SetPosition(const Klein::Math::Vector2<float>& position) noexcept;
		KLEIN_API float GetLocalRotation() const noexcept;
		KLEIN_API void SetLocalRotation(float localRotation) noexcept;
		KLEIN_API float GetRotation() const noexcept;
		KLEIN_API void SetRotation(float rotation) noexcept;
		KLEIN_API const Klein::Math::Vector2<float>& GetLocalScale() const noexcept;
		KLEIN_API void SetLocalScale(const Klein::Math::Vector2<float>& localScale) noexcept;
		KLEIN_API Klein::Math::Vector2<float> GetScale() const noexcept;
		KLEIN_API void SetScale(const Klein::Math::Vector2<float>& scale) noexcept;
		KLEIN_API const std::vector<std::shared_ptr<Node>>& GetChildren() const noexcept;
		KLEIN_API std::vector<std::shared_ptr<Node>>& GetChildren(std::vector<std::shared_ptr<Node>>& result) const;
		KLEIN_API std::shared_ptr<Node> CreateNewChild();
		KLEIN_API std::shared_ptr<Node> CreateNewChild(const std::string& name);
		KLEIN_API std::shared_ptr<Node> CreateNewChild(std::string&& name);
		KLEIN_API std::shared_ptr<Node> CreateNewAndInsertChild(std::size_t index);
		KLEIN_API std::shared_ptr<Node> CreateNewAndInsertChild(std::size_t index, const std::string& name);
		KLEIN_API std::shared_ptr<Node> CreateNewAndInsertChild(std::size_t index, std::string&& name);
		KLEIN_API bool RemoveChild(std::size_t index);
		KLEIN_API bool RemoveChild(std::shared_ptr<Node> child);
		KLEIN_API void RemoveAllChildren() noexcept;
		KLEIN_API const std::vector<std::shared_ptr<Klein::Scripting::Script>>& GetScripts() const noexcept;
		KLEIN_API std::vector<std::shared_ptr<Klein::Scripting::Script>>& GetScripts(
			std::vector<std::shared_ptr<Klein::Scripting::Script>>& result
		) const;
		template <typename TScript>
		constexpr inline std::shared_ptr<TScript> AddScript() {
			static_assert(
				std::is_base_of<Klein::Scripting::Script, TScript>::value,
				"Specified type is not derived from Klein::Scripting::Script.");
			std::shared_ptr<TScript> ret(std::make_shared<TScript>(this));
			scripts.push_back(ret);
			OnScriptAdded(ret);
			return ret;
		}
		template <typename TScript>
		constexpr inline std::shared_ptr<TScript> EnsureScript() {
			static_assert(
				std::is_base_of<Klein::Scripting::Script, TScript>::value,
				"Specified type is not derived from Klein::Scripting::Script.");
			std::shared_ptr<TScript> ret;
			if (!TryGettingScript<TScript>(ret)) {
				ret = AddScript<TScript>();
			}
			return ret;
		}
		template <typename TScript>
		constexpr bool IsScriptAvailable() const noexcept {
			static_assert(
				std::is_base_of<Klein::Scripting::Script, TScript>::value,
				"Specified type is not derived from Klein::Scripting::Script.");
			bool ret(false);
			for (const auto& script : scripts) {
				if (dynamic_cast<TScript*>(script.get())) {
					ret = true;
					break;
				}
			}
			return ret;
		}
		template <typename TScript>
		constexpr bool TryGettingScript(const std::shared_ptr<TScript>& result) const noexcept {
			static_assert(
				std::is_base_of<Klein::Scripting::Script, TScript>::value,
				"Specified type is not derived from Klein::Scripting::Script.");
			bool ret(false);
			for (const auto& script : scripts) {
				result = std::dynamic_pointer_cast<TScript>(script);
				if (result) {
					ret = true;
					break;
				}
			}
			return ret;
		}
		template <typename TScript>
		constexpr bool TryGettingScript(std::shared_ptr<TScript>& result) noexcept {
			static_assert(
				std::is_base_of<Klein::Scripting::Script, TScript>::value,
				"Specified type is not derived from Klein::Scripting::Script.");
			bool ret(false);
			for (auto& script : scripts) {
				result = std::dynamic_pointer_cast<TScript>(script);
				if (result) {
					ret = true;
					break;
				}
			}
			return ret;
		}
		template <typename TScript>
		constexpr std::vector<std::shared_ptr<TScript>>& GetScripts(std::vector<std::shared_ptr<TScript>>& result) const {
			static_assert(
				std::is_base_of<Klein::Scripting::Script, TScript>::value,
				"Specified type is not derived from Klein::Scripting::Script.");
			result.clear();
			for (const auto& script : scripts) {
				if (dynamic_cast<TScript*>(script.get())) {
					result.push_back(script);
				}
			}
			return result;
		}
		template <typename TScript>
		constexpr bool RemoveScript(const std::shared_ptr<TScript>& script) {
			static_assert(
				std::is_base_of<Klein::Scripting::Script, TScript>::value,
				"Specified type is not derived from Klein::Scripting::Script.");
			bool ret(false);
			if (script) {
				const auto& it(std::find(scripts.begin(), scripts.end(), script));
				if (it != scripts.end()) {
					OnScriptRemoved(script);
					script->Deinitialize();
					scripts.erase(it);
					ret = true;
				}
			}
			return ret;
		}
		template <typename TScript>
		constexpr std::size_t RemoveScripts() {
			static_assert(
				std::is_base_of<Klein::Scripting::Script, TScript>::value,
				"Specified type is not derived from Klein::Scripting::Script.");
			std::size_t ret(0U);
			std::vector<std::shared_ptr<TScript>> scripts;
			for (const auto& script : GetScripts<TScript>(scripts)) {
				if (RemoveScript<TScript>(script)) {
					++ret;
				}
			}
			return ret;
		}
		KLEIN_API void RemoveAllScripts();
		KLEIN_API void GameTickScripts(Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		KLEIN_API void BeforeFrameRenderScripts(Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		KLEIN_API void FrameRenderScripts(Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		KLEIN_API void Destroy();

		Node& operator =(const Node&) = delete;
		Node& operator =(Node&&) noexcept = delete;

	private:

		Node* parent;
		bool isLocallyEnabled;
		bool isMarkedForDeletion;
		std::string name;
		Klein::Math::Vector2<float> localPosition;
		float localRotation;
		Klein::Math::Vector2<float> localScale;
		std::vector<std::shared_ptr<Node>> children;
		std::vector<std::shared_ptr<Klein::Scripting::Script>> scripts;
		std::vector<std::shared_ptr<Klein::Scripting::Script>> temporaryScripts;
	};
}
