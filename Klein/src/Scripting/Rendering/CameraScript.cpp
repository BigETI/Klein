#include <cstddef>
#include <chrono>

#include <Klein/Engine.hpp>
#include <Klein/Rendering/RenderingContext.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Rendering/CameraScript.hpp>
#include <Klein/Scripting/Script.hpp>

using namespace std;
using namespace std::chrono;

using namespace Klein;
using namespace Klein::Rendering;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting;
using namespace Klein::Scripting::Rendering;

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
