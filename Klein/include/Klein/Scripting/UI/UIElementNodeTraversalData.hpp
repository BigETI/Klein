#pragma once

#include "../../SceneManagement/Node.hpp"

namespace Klein::Scripting::UI {
	struct UIElementNodeTraversalData {
		Klein::SceneManagement::Node* node;
		bool hasChildrenListed;
	};
}
