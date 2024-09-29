#include <cstddef>
#include <chrono>

#include <NGE/Engine.hpp>
#include <NGE/Rendering/RenderingContext.hpp>
#include <NGE/SceneManagement/Node.hpp>
#include <NGE/Scripting/Rendering/CameraScript.hpp>
#include <NGE/Scripting/Script.hpp>

using namespace std;
using namespace std::chrono;

using namespace NGE;
using namespace NGE::Rendering;
using namespace NGE::SceneManagement;
using namespace NGE::Scripting;
using namespace NGE::Scripting::Rendering;

CameraScript::CameraScript(Node* node) : Script(node), cameraIndex(static_cast<size_t>(0U)), cameraZoom(1.0f) {
	// ...
}

size_t CameraScript::GetCameraIndex() const noexcept {
	return cameraIndex;
}

void CameraScript::SetCameraIndex(size_t cameraIndex) noexcept {
	this->cameraIndex = cameraIndex;
}

float CameraScript::GetCameraZoom() const noexcept {
	return cameraZoom;
}

void CameraScript::SetCameraZoom(float cameraZoom) noexcept {
	this->cameraZoom = cameraZoom;
}

void CameraScript::OnFrameRender(Engine& engine, high_resolution_clock::duration deltaTime) {
	if (cameraIndex >= engine.GetRenderingContexts().size()) {
		engine.GetRenderingContexts().resize(cameraIndex + static_cast<size_t>(1U));
	}
	RenderingContext& rendering_context(engine.GetRenderingContexts().at(cameraIndex));
	rendering_context.SetCameraPosition(GetNode().GetPosition());
	rendering_context.SetCameraRotation(GetNode().GetRotation());
	rendering_context.SetCameraZoom(cameraZoom);
}
