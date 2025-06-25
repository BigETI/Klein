#pragma once

#include "../../EventSystem/Event.hpp"
#include "../../Exportables/Exportable.hxx"
#include "../../InputSystem/InputEvent.hpp"
#include "../../SceneManagement/Node.hpp"
#include "ImageScript.hpp"

namespace Klein::Scripting::UI {
	class ButtonScript : public ImageScript {
	public:

		Klein::EventSystem::Event<> OnClicked;

		KLEIN_API ButtonScript(Klein::SceneManagement::Node* node);

		KLEIN_API virtual bool ConsumeInputEvent(const Klein::InputSystem::InputEvent& inputEvent) override;
	};
}
