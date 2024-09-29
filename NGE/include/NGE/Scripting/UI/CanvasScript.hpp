#pragma once

#include <chrono>
#include <memory>
#include <vector>

#include "../../EventSystem/ObserverID.hpp"
#include "../../Exportables/Exportable.hxx"
#include "../../Engine.hpp"
#include "../../Hashing/StringHash.hpp"
#include "../../InputSystem/InputEvent.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"
#include "UIElementScript.hpp"

namespace NGE::Scripting::UI {
	class CanvasScript : public NGE::Scripting::Script {
	public:

		NGE_API CanvasScript(NGE::SceneManagement::Node* node);
		NGE_API ~CanvasScript();

		NGE_API virtual void OnFrameRender(NGE::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime) override;

	private:

		static const NGE::Hashing::StringHash mousePositionNameHash;
		static const NGE::InputSystem::InputEvent uiCursorPositionInputEvent;
		bool isRebuildingChildNodeCache;
		NGE::EventSystem::ObserverID childAddedObserverID;
		NGE::EventSystem::ObserverID childRemovedObserverID;
		NGE::EventSystem::ObserverID scriptAddedObserverID;
		NGE::EventSystem::ObserverID scriptRemovedObserverID;
		std::vector<std::shared_ptr<UIElementScript>> cachedUIElements;

		void UpdateRebuildingChildNodeCacheState(const std::shared_ptr<NGE::Scripting::Script>& script);
	};
}
