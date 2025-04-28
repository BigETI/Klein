#include <utility>

#include <Klein/Math/Rectangle.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Physics/AABBColliderScript.hpp>
#include <Klein/Scripting/Physics/ColliderScript.hpp>

using namespace Klein::Math;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting::Physics;

AABBColliderScript::AABBColliderScript(Node* node) : ColliderScript(node) {
	// ...
}

const Rectangle<float>& AABBColliderScript::GetLocalCollisionRectangle() const noexcept {
	return localCollisionRectangle;
}
void AABBColliderScript::SetLocalCollisionRectangle(const Klein::Math::Rectangle<float>& localCollisionRectangle) noexcept {
	this->localCollisionRectangle = localCollisionRectangle;
}

void AABBColliderScript::SetLocalCollisionRectangle(Klein::Math::Rectangle<float>&& localCollisionRectangle) noexcept {
	this->localCollisionRectangle = std::move(localCollisionRectangle);
}

Rectangle<float> AABBColliderScript::GetCollisionRectangle() const noexcept {
	return Rectangle<float>(GetNode().GetPosition() + localCollisionRectangle.position, GetNode().GetScale() * localCollisionRectangle.size);
}
