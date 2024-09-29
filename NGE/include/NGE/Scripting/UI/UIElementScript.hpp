#pragma once

#include "../../EventSystem/Event.hpp"
#include "../../Exportables/Exportable.hxx"
#include "../../Math/Bounds.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Math/Vector2.hpp"
#include "../../InputSystem/InputEvent.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"

namespace NGE::Scripting::UI {
	class UIElementScript : public NGE::Scripting::Script {
	public:
		NGE_API UIElementScript(NGE::SceneManagement::Node* node);
		NGE_API virtual ~UIElementScript() noexcept;

		NGE_API const NGE::Math::Bounds<float>& GetAnchor() const noexcept;
		NGE_API void SetAnchor(const NGE::Math::Bounds<float>& anchor) noexcept;
		NGE_API void SetAnchor(NGE::Math::Bounds<float>&& anchor) noexcept;
		NGE_API const NGE::Math::Bounds<float>& GetBounds() const noexcept;
		NGE_API void SetBounds(const NGE::Math::Bounds<float>& bounds) noexcept;
		NGE_API void SetBounds(NGE::Math::Bounds<float>&& bounds) noexcept;
		NGE_API const NGE::Math::Bounds<float>& GetMargin() const noexcept;
		NGE_API void SetMargin(const NGE::Math::Bounds<float>& margin) noexcept;
		NGE_API void SetMargin(NGE::Math::Bounds<float>&& margin) noexcept;
		NGE_API NGE::Math::Rectangle<float> GetAbsoluteRectangle(const NGE::Math::Rectangle<float>& relativeToRectangle) const noexcept;
		NGE_API virtual bool ApplyInputEvent(const NGE::InputSystem::InputEvent& inputEvent);

	private:

		// TODO: Define UI element attributes
		NGE::Math::Bounds<float> anchor;
		NGE::Math::Bounds<float> bounds;
		NGE::Math::Bounds<float> margin;
	};
}
