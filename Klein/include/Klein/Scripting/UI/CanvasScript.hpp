#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <vector>

#include "../../EventSystem/ObserverID.hpp"
#include "../../Exportables/Exportable.hxx"
#include "../../Engine.hpp"
#include "../../Hashing/StringHash.hpp"
#include "../../InputSystem/InputEvent.hpp"
#include "../../Math/Bounds.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Rendering/RenderingContextScript.hpp"
#include "UIElementScript.hpp"

namespace Klein::Scripting::UI {
	class CanvasScript : public Klein::Scripting::Rendering::RenderingContextScript {
	public:

		KLEIN_API CanvasScript(Klein::SceneManagement::Node* node);

		KLEIN_API virtual void OnFrameRender(Klein::Engine& engine, const std::chrono::high_resolution_clock::duration& deltaTime) override;

	private:

		Klein::Math::Vector2<float> lastUICursorPosition;

		static Klein::Math::Bounds<float> GetOuterBounds(const UIElementScript& uiElement, const Klein::Math::Bounds<float>& parentBounds) noexcept;
		bool ForwardInputEventToNode(const Klein::InputSystem::InputEvent& inputEvent, Klein::SceneManagement::Node& node, const Klein::Math::Bounds<float>& parentBounds);
		void RenderUINode(Klein::Rendering::RenderingContext& renderingContext, Klein::SceneManagement::Node& node, const Klein::Math::Bounds<float>& parentBounds);
	};
}
