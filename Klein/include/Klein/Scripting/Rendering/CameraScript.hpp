#pragma once

#include <chrono>
#include <cstddef>

#include "../../Exportables/Exportable.hxx"
#include "../../Engine.hpp"
#include "../../SceneManagement/Node.hpp"
#include "RenderingContextScript.hpp"

namespace Klein::Scripting::Rendering {
	class CameraScript : public RenderingContextScript {
	public:

		KLEIN_API CameraScript(Klein::SceneManagement::Node* node);

		KLEIN_API float GetCameraZoom() const noexcept;
		KLEIN_API void SetCameraZoom(float cameraZoom) noexcept;

	protected:

		KLEIN_API virtual void OnFrameRender(Klein::Engine& engine, const std::chrono::high_resolution_clock::duration& deltaTime) override;

	private:

		float cameraZoom;
	};
}
