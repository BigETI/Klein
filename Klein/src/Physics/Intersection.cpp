#include <memory>

#include <Klein/Physics/Intersection.hpp>
#include <Klein/Scripting/Physics/ColliderScript.hpp>

using namespace std;

using namespace Klein::Physics;
using namespace Klein::Scripting::Physics;

Intersection::Intersection(const ColliderScript* sourceCollider, const ColliderScript* destinationCollider) :
	sourceCollider(sourceCollider),
	destinationCollider(destinationCollider) {
	// ...
}
