#pragma once

#include <chrono>

#include "RenderingContext.hpp"

namespace Klein::Rendering {
	class IRenderer {
	public:

		virtual ~IRenderer() noexcept {
			// ...
		}

		virtual void Render(const RenderingContext& renderingContext, std::chrono::high_resolution_clock::duration deltaTime) = 0;
	};
}
