#pragma once

#include <chrono>
#include <cstddef>

#include "../../Exportables/Exportable.hxx"
#include "../../Engine.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Script.hpp"

namespace NGE::Scripting::Rendering {
	class CameraScript : public Script {
	public:

		NGE_API CameraScript(NGE::SceneManagement::Node* node);

		NGE_API std::size_t GetCameraIndex() const noexcept;
		NGE_API void SetCameraIndex(std::size_t cameraIndex) noexcept;
		NGE_API float GetCameraZoom() const noexcept;
		NGE_API void SetCameraZoom(float cameraZoom) noexcept;

	protected:

		NGE_API virtual void OnFrameRender(NGE::Engine& engine, std::chrono::high_resolution_clock::duration deltaTime) override;

	private:

		std::size_t cameraIndex;
		float cameraZoom;
	};
}
