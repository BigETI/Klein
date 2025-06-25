#pragma once

#include "../../Exportables/Exportable.hxx"
#include "../../Math/Border.hpp"
#include "../../Math/Bounds.hpp"
#include "../../Math/Vector2.hpp"
#include "../../InputSystem/InputEvent.hpp"
#include "../../Rendering/RenderingContext.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"

namespace Klein::Scripting::UI {
	class UIElementScript : public Klein::Scripting::Script {
	public:
		KLEIN_API UIElementScript(Klein::SceneManagement::Node* node);
		KLEIN_API virtual ~UIElementScript() noexcept;

		KLEIN_API const Klein::Math::Vector2<float>& GetPosition() const noexcept;
		KLEIN_API void SetPosition(const Klein::Math::Vector2<float>& position) noexcept;
		KLEIN_API void SetPosition(Klein::Math::Vector2<float>&& position) noexcept;
		KLEIN_API const Klein::Math::Bounds<float>& GetAnchor() const noexcept;
		KLEIN_API void SetAnchor(const Klein::Math::Bounds<float>& anchor) noexcept;
		KLEIN_API void SetAnchor(Klein::Math::Bounds<float>&& anchor) noexcept;
		KLEIN_API const Klein::Math::Border<float>& GetBorder() const noexcept;
		KLEIN_API void SetBorder(const Klein::Math::Border<float>& border) noexcept;
		KLEIN_API void SetBorder(Klein::Math::Border<float>&& border) noexcept;
		KLEIN_API const Klein::Math::Border<float>& GetMargin() const noexcept;
		KLEIN_API void SetMargin(const Klein::Math::Border<float>& margin) noexcept;
		KLEIN_API void SetMargin(Klein::Math::Border<float>&& margin) noexcept;
		KLEIN_API const Klein::Math::Border<float>& GetPadding() const noexcept;
		KLEIN_API void SetPadding(const Klein::Math::Border<float>& padding) noexcept;
		KLEIN_API void SetPadding(Klein::Math::Border<float>&& padding) noexcept;
		KLEIN_API virtual bool ConsumeInputEvent(const Klein::InputSystem::InputEvent& inputEvent);
		KLEIN_API virtual void OnUIRender(Klein::Rendering::RenderingContext& renderingContext, const Klein::Math::Bounds<float>& bounds);

	private:

		Klein::Math::Vector2<float> position;
		Klein::Math::Bounds<float> anchor;
		Klein::Math::Border<float> border;
		Klein::Math::Border<float> margin;
		Klein::Math::Border<float> padding;
	};
}
