#pragma once

#include <chrono>
#include <cstddef>

#include "../../Exportables/Exportable.hxx"
#include "../../Engine.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"

namespace Klein::Scripting::Rendering {
	class CameraScript : public Script {
	public:

		KLEIN_API CameraScript(Klein::SceneManagement::Node* node);

		KLEIN_API std::size_t GetCameraIndex() const noexcept;
		KLEIN_API void SetCameraIndex(std::size_t cameraIndex) noexcept;
		KLEIN_API float GetCameraZoom() const noexcept;
		KLEIN_API void SetCameraZoom(float cameraZoom) noexcept;

	protected:

		KLEIN_API virtual void OnFrameRender(Klein::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime) override;

	private:

		std::size_t cameraIndex;
		float cameraZoom;
	};
}
