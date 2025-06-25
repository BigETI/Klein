#pragma once

#include <chrono>
#include <cstddef>

#include "../../Engine.hpp"
#include "../../Rendering/RenderingContext.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"

namespace Klein::Scripting::Rendering {
	class RenderingContextScript : public Klein::Scripting::Script {
	public:

		KLEIN_API RenderingContextScript(Klein::SceneManagement::Node* node);

		KLEIN_API std::size_t GetRenderingContextIndex() const noexcept;
		KLEIN_API void SetRenderingContextIndex(std::size_t renderingContextIndex) noexcept;
		KLEIN_API Klein::Rendering::RenderingContext& EnsureRenderingContext(Klein::Engine& engine);

	private:

		std::size_t renderingContextIndex;
	};
}
