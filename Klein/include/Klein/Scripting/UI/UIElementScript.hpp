#pragma once

#include "../../EventSystem/Event.hpp"
#include "../../Exportables/Exportable.hxx"
#include "../../Math/Bounds.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Math/Vector2.hpp"
#include "../../InputSystem/InputEvent.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"

namespace Klein::Scripting::UI {
	class UIElementScript : public Klein::Scripting::Script {
	public:
		KLEIN_API UIElementScript(Klein::SceneManagement::Node* node);
		KLEIN_API virtual ~UIElementScript() noexcept;

		KLEIN_API const Klein::Math::Bounds<float>& GetAnchor() const noexcept;
		KLEIN_API void SetAnchor(const Klein::Math::Bounds<float>& anchor) noexcept;
		KLEIN_API void SetAnchor(Klein::Math::Bounds<float>&& anchor) noexcept;
		KLEIN_API const Klein::Math::Bounds<float>& GetBounds() const noexcept;
		KLEIN_API void SetBounds(const Klein::Math::Bounds<float>& bounds) noexcept;
		KLEIN_API void SetBounds(Klein::Math::Bounds<float>&& bounds) noexcept;
		KLEIN_API const Klein::Math::Bounds<float>& GetMargin() const noexcept;
		KLEIN_API void SetMargin(const Klein::Math::Bounds<float>& margin) noexcept;
		KLEIN_API void SetMargin(Klein::Math::Bounds<float>&& margin) noexcept;
		KLEIN_API Klein::Math::Rectangle<float> GetAbsoluteRectangle(const Klein::Math::Rectangle<float>& relativeToRectangle) const noexcept;
		KLEIN_API virtual bool ApplyInputEvent(const Klein::InputSystem::InputEvent& inputEvent);

	private:

		// TODO: Define UI element attributes
		Klein::Math::Bounds<float> anchor;
		Klein::Math::Bounds<float> bounds;
		Klein::Math::Bounds<float> margin;
	};
}
