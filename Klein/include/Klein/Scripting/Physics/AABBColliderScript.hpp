#pragma once

#include "../../Exportables/Exportable.hxx"
#include "../../Math/Rectangle.hpp"
#include "ColliderScript.hpp"

namespace Klein::Scripting::Physics {
	class AABBColliderScript : public ColliderScript {
	public:

		KLEIN_API AABBColliderScript(Klein::SceneManagement::Node* node);

		KLEIN_API const Klein::Math::Rectangle<float>& GetLocalCollisionRectangle() const noexcept;
		KLEIN_API void SetLocalCollisionRectangle(const Klein::Math::Rectangle<float>& localCollisionRectangle) noexcept;
		KLEIN_API void SetLocalCollisionRectangle(Klein::Math::Rectangle<float>&& localCollisionRectangle) noexcept;
		KLEIN_API Klein::Math::Rectangle<float> GetCollisionRectangle() const noexcept;

	private:

		Klein::Math::Rectangle<float> localCollisionRectangle;
	};
}
