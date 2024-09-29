#pragma once

#include "../../SceneManagement/Node.hpp"

namespace NGE::Scripting::UI {
	struct UIElementNodeTraversalData {
		NGE::SceneManagement::Node* node;
		bool hasChildrenListed;
	};
}
