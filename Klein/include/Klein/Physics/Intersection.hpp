#pragma once

#include "../Exportables/Exportable.hxx"
#include "../Scripting/Physics/ColliderScript.hpp"

namespace Klein::Scripting::Physics {
	class ColliderScript;
}

namespace Klein::Physics {
	struct Intersection {

		const Klein::Scripting::Physics::ColliderScript* sourceCollider;

		const Klein::Scripting::Physics::ColliderScript* destinationCollider;

		KLEIN_API Intersection(const Klein::Scripting::Physics::ColliderScript* sourceCollider, const Klein::Scripting::Physics::ColliderScript* destinationCollider);
	};
}
