#include <chrono>
#include <cstddef>

#include <Klein/Engine.hpp>
#include <Klein/Rendering/RenderingContext.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Rendering/RenderingContextScript.hpp>

using namespace std;
using namespace std::chrono;

using namespace Klein::Rendering;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting::Rendering;

RenderingContextScript::RenderingContextScript(Node* node) : Script(node), renderingContextIndex(static_cast<size_t>(0)) {
	// ...
}

size_t RenderingContextScript::GetRenderingContextIndex() const noexcept {
	return renderingContextIndex;
}

void RenderingContextScript::SetRenderingContextIndex(size_t renderingContextIndex) noexcept {
	this->renderingContextIndex = renderingContextIndex;
}

RenderingContext& RenderingContextScript::EnsureRenderingContext(Engine& engine) {
	if (renderingContextIndex >= engine.GetRenderingContexts().size()) {
		engine.GetRenderingContexts().resize(renderingContextIndex + static_cast<size_t>(1U));
	}
	return engine.GetRenderingContexts().at(renderingContextIndex);
}
