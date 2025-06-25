#include <cstddef>
#include <chrono>

#include <Klein/Engine.hpp>
#include <Klein/Rendering/RenderingContext.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Rendering/CameraScript.hpp>
#include <Klein/Scripting/Rendering/RenderingContextScript.hpp>

using namespace std;
using namespace std::chrono;

using namespace Klein;
using namespace Klein::Rendering;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting::Rendering;

CameraScript::CameraScript(Node* node) : RenderingContextScript(node), cameraZoom(1.0f) {
	// ...
}

float CameraScript::GetCameraZoom() const noexcept {
	return cameraZoom;
}

void CameraScript::SetCameraZoom(float cameraZoom) noexcept {
	this->cameraZoom = cameraZoom;
}

void CameraScript::OnFrameRender(Engine& engine, const high_resolution_clock::duration& deltaTime) {
	RenderingContext& rendering_context(EnsureRenderingContext(engine));
	rendering_context.SetCameraPosition(GetNode().GetPosition());
	rendering_context.SetCameraRotation(GetNode().GetRotation());
	rendering_context.SetCameraZoom(cameraZoom);
}
