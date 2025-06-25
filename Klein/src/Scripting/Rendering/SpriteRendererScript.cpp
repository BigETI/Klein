#include <chrono>
#include <memory>
#include <string>

#include <Klein/Engine.hpp>
#include <Klein/Math/Rectangle.hpp>
#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/Color.hpp>
#include <Klein/Rendering/RenderingContextElement.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>
#include <Klein/SceneManagement/Node.hpp>
#include <Klein/Scripting/Rendering/RenderingContextScript.hpp>
#include <Klein/Scripting/Rendering/SpriteRendererScript.hpp>

using namespace std;
using namespace std::chrono;

using namespace Klein;
using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::ResourceManagement;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting::Rendering;

SpriteRendererScript::SpriteRendererScript(Node* node) :
	RenderingContextScript(node),
	renderingContextElement(
		make_shared<RenderingContextElement>(
			true,
			true,
			string(),
			string(),
			Rectangle<float>(Vector2<float>(0.0f, 0.0f), Vector2<float>(1.0f, 1.0f)),
			Rectangle<float>(Vector2<float>(0.0f, 0.0f), Vector2<float>(1.0f, 1.0f)),
			0.0f,
			Vector2<float>(0.5f, 0.5f),
			Color<float>(1.0f, 1.0f, 1.0f, 1.0f),
			string(),
			1.0f,
			0.2f,
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

bool SpriteRendererScript::IsTexture2DVisible() const noexcept {
	return renderingContextElement->IsTexture2DVisible();
}

void SpriteRendererScript::SetTexture2DVisibility(bool isTexture2DVisible) noexcept {
	renderingContextElement->SetTexture2DVisibility(isTexture2DVisible);
}

bool SpriteRendererScript::IsTextVisible() const noexcept {
	return renderingContextElement->IsTextVisible();
}

void SpriteRendererScript::SetTextVisibility(bool isTextVisible) noexcept {
	renderingContextElement->SetTextVisibility(isTextVisible);
}

const ResourceID& SpriteRendererScript::GetTexture2DResourceID() const noexcept {
	return renderingContextElement->GetTexture2DResourceID();
}

ResourceID& SpriteRendererScript::GetTexture2DResourcePath(ResourceID& result) const {
	return result = renderingContextElement->GetTexture2DResourceID();
}

void SpriteRendererScript::SetTexture2DResourceID(const ResourceID& texture2DResourceID) {
	renderingContextElement->SetTexture2DResourceID(texture2DResourceID);
}

void SpriteRendererScript::SetTexture2DResourceID(ResourceID&& texture2DResourceID) noexcept {
	renderingContextElement->SetTexture2DResourceID(std::move(texture2DResourceID));
}

const ResourceID& SpriteRendererScript::GetFontResourceID() const noexcept {
	return renderingContextElement->GetFontResourceID();
}

ResourceID& SpriteRendererScript::GetFontResourcePath(Klein::ResourceManagement::ResourceID& result) const {
	return result = renderingContextElement->GetFontResourceID();
}

void SpriteRendererScript::SetFontResourceID(const Klein::ResourceManagement::ResourceID& fontResourceID) {
	renderingContextElement->SetFontResourceID(fontResourceID);
}

void SpriteRendererScript::SetFontResourceID(Klein::ResourceManagement::ResourceID&& fontResourceID) noexcept {
	renderingContextElement->SetFontResourceID(fontResourceID);
}

const Rectangle<float>& SpriteRendererScript::GetTexture2DSourceRectangle() const noexcept {
	return renderingContextElement->GetTexture2DSourceRectangle();
}

void SpriteRendererScript::SetTexture2DSourceRectangle(const Rectangle<float>& texture2DSourceRectangle) noexcept {
	renderingContextElement->SetTexture2DSourceRectangle(texture2DSourceRectangle);
}

const Vector2<float>& SpriteRendererScript::GetPivot() const noexcept {
	return renderingContextElement->GetPivot();
}

void SpriteRendererScript::SetPivot(const Vector2<float>& pivot) noexcept {
	renderingContextElement->SetPivot(pivot);
}

const Color<float>& SpriteRendererScript::GetColor() const noexcept {
	return renderingContextElement->GetColor();
}

void SpriteRendererScript::SetColor(const Color<float>& color) noexcept {
	renderingContextElement->SetColor(color);
}

const string& SpriteRendererScript::GetText() const noexcept {
	return renderingContextElement->GetText();
}

string& SpriteRendererScript::GetText(string& result) const {
	return renderingContextElement->GetText(result);
}

void SpriteRendererScript::SetText(const string& text) {
	renderingContextElement->SetText(text);
}

void SpriteRendererScript::SetText(string&& text) noexcept {
	renderingContextElement->SetText(text);
}

float SpriteRendererScript::GetTextFontSize() const noexcept {
	return renderingContextElement->GetTextFontSize();
}

void SpriteRendererScript::SetTextFontSize(float textFontSize) noexcept {
	renderingContextElement->SetTextFontSize(textFontSize);
}

float SpriteRendererScript::GetTextSpacing() const noexcept {
	return renderingContextElement->GetTextSpacing();
}

void SpriteRendererScript::SetTextSpacing(float textSpacing) noexcept {
	renderingContextElement->SetTextSpacing(textSpacing);
}

unsigned int SpriteRendererScript::GetLayerIndex() const noexcept {
	return renderingContextElement->GetLayerIndex();
}

void SpriteRendererScript::SetLayerIndex(unsigned int layerIndex) noexcept {
	renderingContextElement->SetLayerIndex(layerIndex);
}

void SpriteRendererScript::OnFrameRender(Engine& engine, const high_resolution_clock::duration& deltaTime) {
	Node& node(GetNode());

	// TODO: Interpolate between transformations
	renderingContextElement->SetRectangle(Rectangle<float>(node.GetPosition(), node.GetScale()));
	renderingContextElement->SetRotation(node.GetRotation());
	EnsureRenderingContext(engine).StageElement(renderingContextElement);
}
