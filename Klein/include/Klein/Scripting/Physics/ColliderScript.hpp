#pragma once

#include <functional>
#include <vector>

#include "../../Exportables/Exportable.hxx"
#include "../../SceneManagement/Node.hpp"
#include "../../Physics/Intersection.hpp"
#include "../Script.hpp"

namespace Klein::Physics {
	struct Intersection;
}

namespace Klein::Scripting::Physics {
	class ColliderScript : public Klein::Scripting::Script {
	public:

		KLEIN_API ColliderScript(Klein::SceneManagement::Node* node);
		KLEIN_API virtual ~ColliderScript() noexcept;

		KLEIN_API void EnumerateIntersections(const std::function<void(const Klein::Physics::Intersection& intersection)>& onIntersectionFound) const noexcept;

	private:

		static std::vector<const ColliderScript*> allColliders;
	};
}
