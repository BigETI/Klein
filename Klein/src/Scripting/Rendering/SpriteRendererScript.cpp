#include <chrono>
#include <cstdint>
#include <memory>
#include <string>

#include <Klein/Engine.hpp>
#include <Klein/Math/Rectangle.hpp>
#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/Color.hpp>
#include <Klein/Rendering/RenderingContextElement.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Rendering/SpriteRendererScript.hpp>
#include <Klein/Scripting/Script.hpp>

using namespace std;
using namespace std::chrono;

using namespace Klein;
using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::ResourceManagement;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting;
using namespace Klein::Scripting::Rendering;

SpriteRendererScript::SpriteRendererScript(Node* node) :
	Script(node),
	renderingContextElement(
		make_shared<RenderingContextElement>(
			string(),
			Rectangle<float>(Vector2<float>(0.0f, 0.0f), Vector2<float>(1.0f, 1.0f)),
			Vector2<float>(),
			0.0f,
			Vector2<float>(1.0f, 1.0f),
			Vector2<float>(0.5f, 0.5f),
			Color<uint8_t>(0xFF, 0xFF, 0xFF, 0xFF),
			0U
		)
	) {
	// ...
}

const shared_ptr<RenderingContextElement>& SpriteRendererScript::GetRenderingContextElement() const noexcept {
	return renderingContextElement;
}

shared_ptr<RenderingContextElement>& SpriteRendererScript::GetRenderingContextElement() noexcept {
	return renderingContextElement;
}

const ResourceID& SpriteRendererScript::GetResourceID() const noexcept {
	return renderingContextElement->GetResourceID();
}

ResourceID& SpriteRendererScript::GetResourcePath(ResourceID& result) const {
	return result = renderingContextElement->GetResourceID();
}

void SpriteRendererScript::SetResourceID(const ResourceID& resourceID) {
	renderingContextElement->SetResourceID(resourceID);
}

void SpriteRendererScript::SetResourceID(ResourceID&& resourceID) noexcept {
	renderingContextElement->SetResourceID(std::move(resourceID));
}

const Rectangle<float>& SpriteRendererScript::GetSourceRectangle() const noexcept {
	return renderingContextElement->GetSourceRectangle();
}

void SpriteRendererScript::SetSourceRectangle(const Rectangle<float>& sourceRectangle) noexcept {
	renderingContextElement->SetSourceRectangle(sourceRectangle);
}

const Vector2<float>& SpriteRendererScript::GetPivot() const noexcept {
	return renderingContextElement->GetPivot();
}

void SpriteRendererScript::SetPivot(const Vector2<float>& pivot) noexcept {
	renderingContextElement->SetPivot(pivot);
}

const Color<uint8_t>& SpriteRendererScript::GetColor() const noexcept {
	return renderingContextElement->GetColor();
}

void SpriteRendererScript::SetColor(const Color<uint8_t>& color) noexcept {
	renderingContextElement->SetColor(color);
}

unsigned int SpriteRendererScript::GetLayerIndex() const noexcept {
	return renderingContextElement->GetLayerIndex();
}

void SpriteRendererScript::SetLayerIndex(unsigned int layerIndex) noexcept {
	renderingContextElement->SetLayerIndex(layerIndex);
}

void SpriteRendererScript::OnFrameRender(Engine& engine, high_resolution_clock::duration deltaTime) {
	Node& node(GetNode());

	// TODO: Interpolate between transformations
	renderingContextElement->SetPosition(node.GetPosition());
	renderingContextElement->SetRotation(node.GetRotation());
	renderingContextElement->SetSize(node.GetScale());

	for (auto& rendering_context : engine.GetRenderingContexts()) {
		rendering_context.StageElement(renderingContextElement);
	}
}
