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

namespace NGE::Scripting {
	class Script;
}

namespace NGE {
	class Engine;
}

namespace NGE::SceneManagement {

	// TODO: Implement proper transformation matrices, and transformation operations
	class Node {
	public:

		static constexpr Node* NullParent = nullptr;
		NGE::EventSystem::Event<const std::shared_ptr<Node>&> OnChildAdded;
		NGE::EventSystem::Event<const std::shared_ptr<Node>&> OnChildRemoved;
		NGE::EventSystem::Event<const std::shared_ptr<NGE::Scripting::Script>&> OnScriptAdded;
		NGE::EventSystem::Event<const std::shared_ptr<NGE::Scripting::Script>&> OnScriptRemoved;

		NGE_API Node(Node* parent);
		NGE_API Node(Node* parent, const std::string& name);
		NGE_API Node(Node* parent, std::string&& name) noexcept;
		NGE_API ~Node();

		Node(const Node&) = delete;
		Node(Node&&) noexcept = delete;

		NGE_API Node* GetParent() const noexcept;
		NGE_API bool IsLocallyEnabled() const noexcept;
		NGE_API bool IsEnabled() const noexcept;
		NGE_API void Enable();
		NGE_API void Disable();
		NGE_API bool IsMarkedForDeletion() const noexcept;
		NGE_API const std::string& GetName() const noexcept;
		NGE_API std::string& GetName(std::string& result) const;
		NGE_API void SetName(const std::string& name);
		NGE_API void SetName(std::string&& name) noexcept;
		NGE_API const NGE::Math::Vector2<float>& GetLocalPosition() const noexcept;
		NGE_API void SetLocalPosition(const NGE::Math::Vector2<float>& localPosition) noexcept;
		NGE_API NGE::Math::Vector2<float> GetPosition() const noexcept;
		//NGE_API void SetPosition(const NGE::Math::Vector2<float>& position) noexcept;
		NGE_API float GetLocalRotation() const noexcept;
		NGE_API void SetLocalRotation(float localRotation) noexcept;
		NGE_API float GetRotation() const noexcept;
		NGE_API void SetRotation(float rotation) noexcept;
		NGE_API const NGE::Math::Vector2<float>& GetLocalScale() const noexcept;
		NGE_API void SetLocalScale(const NGE::Math::Vector2<float>& localScale) noexcept;
		NGE_API NGE::Math::Vector2<float> GetScale() const noexcept;
		NGE_API void SetScale(const NGE::Math::Vector2<float>& scale) noexcept;
		NGE_API const std::vector<std::shared_ptr<Node>>& GetChildren() const noexcept;
		NGE_API std::vector<std::shared_ptr<Node>>& GetChildren(std::vector<std::shared_ptr<Node>>& result) const;
		NGE_API std::shared_ptr<Node> CreateNewChild();
		NGE_API std::shared_ptr<Node> CreateNewChild(const std::string& name);
		NGE_API std::shared_ptr<Node> CreateNewChild(std::string&& name);
		NGE_API std::shared_ptr<Node> CreateNewAndInsertChild(std::size_t index);
		NGE_API std::shared_ptr<Node> CreateNewAndInsertChild(std::size_t index, const std::string& name);
		NGE_API std::shared_ptr<Node> CreateNewAndInsertChild(std::size_t index, std::string&& name);
		NGE_API bool RemoveChild(std::size_t index);
		NGE_API bool RemoveChild(std::shared_ptr<Node> child);
		NGE_API void RemoveAllChildren() noexcept;
		NGE_API const std::vector<std::shared_ptr<NGE::Scripting::Script>>& GetScripts() const noexcept;
		NGE_API std::vector<std::shared_ptr<NGE::Scripting::Script>>& GetScripts(
			std::vector<std::shared_ptr<NGE::Scripting::Script>>& result
		) const;
		template <typename TScript>
		constexpr inline std::shared_ptr<TScript> AddScript() {
			static_assert(
				std::is_base_of<NGE::Scripting::Script, TScript>::value,
				"Specified type is not derived from NGE::Scripting::Script.");
			std::shared_ptr<TScript> ret(std::make_shared<TScript>(this));
			scripts.push_back(ret);
			OnScriptAdded(ret);
			return ret;
		}
		template <typename TScript>
		constexpr inline std::shared_ptr<TScript> EnsureScript() {
			static_assert(
				std::is_base_of<NGE::Scripting::Script, TScript>::value,
				"Specified type is not derived from NGE::Scripting::Script.");
			std::shared_ptr<TScript> ret;
			if (!TryGettingScript<TScript>(ret)) {
				ret = AddScript<TScript>();
			}
			return ret;
		}
		template <typename TScript>
		constexpr bool IsScriptAvailable() const noexcept {
			static_assert(
				std::is_base_of<NGE::Scripting::Script, TScript>::value,
				"Specified type is not derived from NGE::Scripting::Script.");
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
				std::is_base_of<NGE::Scripting::Script, TScript>::value,
				"Specified type is not derived from NGE::Scripting::Script.");
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
				std::is_base_of<NGE::Scripting::Script, TScript>::value,
				"Specified type is not derived from NGE::Scripting::Script.");
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
				std::is_base_of<NGE::Scripting::Script, TScript>::value,
				"Specified type is not derived from NGE::Scripting::Script.");
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
				std::is_base_of<NGE::Scripting::Script, TScript>::value,
				"Specified type is not derived from NGE::Scripting::Script.");
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
				std::is_base_of<NGE::Scripting::Script, TScript>::value,
				"Specified type is not derived from NGE::Scripting::Script.");
			std::size_t ret(0U);
			std::vector<std::shared_ptr<TScript>> scripts;
			for (const auto& script : GetScripts<TScript>(scripts)) {
				if (RemoveScript<TScript>(script)) {
					++ret;
				}
			}
			return ret;
		}
		NGE_API void RemoveAllScripts();
		NGE_API void GameTickScripts(Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		NGE_API void BeforeFrameRenderScripts(Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		NGE_API void FrameRenderScripts(Engine& engine, std::chrono::high_resolution_clock::duration deltaTime);
		NGE_API void Destroy();

		Node& operator =(const Node&) = delete;
		Node& operator =(Node&&) noexcept = delete;

	private:

		Node* parent;
		bool isLocallyEnabled;
		bool isMarkedForDeletion;
		std::string name;
		NGE::Math::Vector2<float> localPosition;
		float localRotation;
		NGE::Math::Vector2<float> localScale;
		std::vector<std::shared_ptr<Node>> children;
		std::vector<std::shared_ptr<NGE::Scripting::Script>> scripts;
		std::vector<std::shared_ptr<NGE::Scripting::Script>> temporaryScripts;
	};
}
