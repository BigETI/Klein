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

namespace Klein::Scripting::UI {
	class CanvasScript : public Klein::Scripting::Script {
	public:

		KLEIN_API CanvasScript(Klein::SceneManagement::Node* node);
		KLEIN_API ~CanvasScript();

		KLEIN_API virtual void OnFrameRender(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime) override;

	private:

		static const Klein::Hashing::StringHash mousePositionNameHash;
		static const Klein::InputSystem::InputEvent uiCursorPositionInputEvent;
		bool isRebuildingChildNodeCache;
		Klein::EventSystem::ObserverID childAddedObserverID;
		Klein::EventSystem::ObserverID childRemovedObserverID;
		Klein::EventSystem::ObserverID scriptAddedObserverID;
		Klein::EventSystem::ObserverID scriptRemovedObserverID;
		std::vector<std::shared_ptr<UIElementScript>> cachedUIElements;

		void UpdateRebuildingChildNodeCacheState(const std::shared_ptr<Klein::Scripting::Script>& script);
	};
}
