#pragma once

#include <chrono>
#include <cstddef>
#include <vector>

#include "RenderingContext.hpp"

namespace Klein::Rendering {
	class IRenderer {
	public:

		virtual ~IRenderer() noexcept {
			// ...
		}

		virtual const std::size_t GetWidth() const noexcept = 0;
		virtual const std::size_t GetHeight() const noexcept = 0;
		virtual void Render(const std::vector<RenderingContext>& renderingContexts, const std::chrono::high_resolution_clock::duration& deltaTime) = 0;
	};
}
