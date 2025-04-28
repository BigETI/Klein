#include <functional>
#include <iterator>

#include <Klein/Math/Bounds.hpp>
#include <Klein/Math/EAlignment.hpp>
#include <Klein/Math/Rectangle.hpp>
#include <Klein/Physics/Intersection.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Physics/AABBColliderScript.hpp>
#include <Klein/Scripting/Physics/ColliderScript.hpp>
#include <Klein/Scripting/Script.hpp>

using namespace std;

using namespace Klein::Math;
using namespace Klein::Physics;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting;
using namespace Klein::Scripting::Physics;

vector<const ColliderScript*> ColliderScript::allColliders;

ColliderScript::ColliderScript(Node* node) : Script(node) {
	allColliders.push_back(this);
}

ColliderScript::~ColliderScript() noexcept {
	vector<const ColliderScript*> all_colliders;
	std::copy_if(allColliders.begin(), allColliders.end(), std::back_inserter(all_colliders), [this](const ColliderScript* collider) {
		return collider != this;
	});
	allColliders = all_colliders;
}

void ColliderScript::EnumerateIntersections(const function<void(const Intersection& intersection)>& onIntersectionFound) const noexcept {
	const AABBColliderScript* aabb_collider(dynamic_cast<const AABBColliderScript*>(this));
	if (aabb_collider) {
		Rectangle<float> collision_rectangle(aabb_collider->GetCollisionRectangle());
		for (const auto& another_collider : allColliders) {
			if (another_collider == this) {
				continue;
			}
			const AABBColliderScript* another_aabb_collider(dynamic_cast<const AABBColliderScript*>(another_collider));
			if (another_aabb_collider && collision_rectangle.GetBounds(EAlignment::Center).IsIntersecting(another_aabb_collider->GetCollisionRectangle().GetBounds(EAlignment::Center))) {
				onIntersectionFound(Intersection(this, another_aabb_collider));
			}
		}
	}
}
