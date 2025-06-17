#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>

#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/Color.hpp>
#include <Klein/Rendering/RenderingContextElement.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>

using namespace std;

using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::ResourceManagement;

RenderingContextElement::RenderingContextElement() : rotation(0.0f), layerIndex(0U) {
	// ...
}

RenderingContextElement::RenderingContextElement(
	bool isTexture2DVisible,
	bool isTextVisible,
	const ResourceID& texture2DResourceID,
	const ResourceID& fontResourceID,
	const Rectangle<float>& sourceRectangle,
	const Vector2<float>& position,
	float rotation,
	const Vector2<float>& size,
	const Vector2<float>& pivot,
	const Color<uint8_t>& color,
	const string& text,
	float textFontSize,
	float textSpacing,
	unsigned int layerIndex
) :
	isTexture2DVisible(isTexture2DVisible),
	isTextVisible(isTextVisible),
	texture2DResourceID(texture2DResourceID),
	fontResourceID(fontResourceID),
	sourceRectangle(sourceRectangle),
	position(position),
	rotation(rotation),
	size(size),
	pivot(pivot),
	color(color),
	text(text),
	textFontSize(textFontSize),
	textSpacing(textSpacing),
	layerIndex(layerIndex) {
	// ...
}

RenderingContextElement::RenderingContextElement(
	bool isTexture2DVisible,
	bool isTextVisible,
	ResourceID&& texture2DResourceID,
	ResourceID&& fontResourceID,
	Rectangle<float>&& sourceRectangle,
	Vector2<float>&& position,
	float rotation,
	Vector2<float>&& size,
	Vector2<float>&& pivot,
	Color<uint8_t>&& color,
	string&& text,
	float textFontSize,
	float textSpacing,
	unsigned int layerIndex
) noexcept :
	isTexture2DVisible(isTexture2DVisible),
	isTextVisible(isTextVisible),
	texture2DResourceID(texture2DResourceID),
	fontResourceID(fontResourceID),
	sourceRectangle(sourceRectangle),
	position(position),
	rotation(rotation),
	size(size),
	pivot(pivot),
	color(color),
	text(text),
	textFontSize(textFontSize),
	textSpacing(textSpacing),
	layerIndex(layerIndex) {
	// ...
}

RenderingContextElement::RenderingContextElement(const RenderingContextElement& renderingContextElement) :
	isTexture2DVisible(renderingContextElement.isTexture2DVisible),
	isTextVisible(renderingContextElement.isTextVisible),
	texture2DResourceID(renderingContextElement.texture2DResourceID),
	fontResourceID(renderingContextElement.fontResourceID),
	sourceRectangle(renderingContextElement.sourceRectangle),
	position(renderingContextElement.position),
	rotation(renderingContextElement.rotation),
	size(renderingContextElement.size),
	pivot(renderingContextElement.pivot),
	color(renderingContextElement.color),
	text(renderingContextElement.text),
	textFontSize(renderingContextElement.textFontSize),
	textSpacing(renderingContextElement.textSpacing),
	layerIndex(renderingContextElement.layerIndex) {
	// ...
}

RenderingContextElement::RenderingContextElement(RenderingContextElement&& renderingContextElement) noexcept :
	isTexture2DVisible(std::move(renderingContextElement.isTexture2DVisible)),
	isTextVisible(std::move(renderingContextElement.isTextVisible)),
	texture2DResourceID(std::move(renderingContextElement.texture2DResourceID)),
	fontResourceID(std::move(renderingContextElement.fontResourceID)),
	sourceRectangle(std::move(renderingContextElement.sourceRectangle)),
	position(std::move(renderingContextElement.position)),
	rotation(std::move(renderingContextElement.rotation)),
	size(std::move(renderingContextElement.size)),
	pivot(std::move(renderingContextElement.pivot)),
	color(std::move(renderingContextElement.color)),
	text(std::move(renderingContextElement.text)),
	textFontSize(std::move(renderingContextElement.textFontSize)),
	textSpacing(std::move(renderingContextElement.textSpacing)),
	layerIndex(std::move(renderingContextElement.layerIndex)) {
	// ...
}

bool RenderingContextElement::IsTexture2DVisible() const noexcept {
	return isTexture2DVisible;
}

void RenderingContextElement::SetTexture2DVisibility(bool isTexture2DVisible) noexcept {
	this->isTexture2DVisible = isTexture2DVisible;
}

bool RenderingContextElement::IsTextVisible() const noexcept {
	return isTextVisible;
}

void RenderingContextElement::SetTextVisibility(bool isTextVisible) noexcept {
	this->isTextVisible = isTextVisible;
}

const ResourceID& RenderingContextElement::GetTexture2DResourceID() const noexcept {
	return texture2DResourceID;
}

ResourceID& RenderingContextElement::GetTexture2DResourceID(ResourceID& result) const {
	return result = texture2DResourceID;
}

void RenderingContextElement::SetTexture2DResourceID(const ResourceID& texture2DResourceID) {
	this->texture2DResourceID = texture2DResourceID;
}

void RenderingContextElement::SetTexture2DResourceID(ResourceID&& texture2DResourceID) noexcept {
	this->texture2DResourceID = texture2DResourceID;
}

const ResourceID& RenderingContextElement::GetFontResourceID() const noexcept {
	return fontResourceID;
}

ResourceID& RenderingContextElement::GetFontResourceID(ResourceID& result) const {
	return result = fontResourceID;
}

void RenderingContextElement::SetFontResourceID(const ResourceID& fontResourceID) {
	this->fontResourceID = fontResourceID;
}

void RenderingContextElement::SetFontResourceID(ResourceID&& fontResourceID) noexcept {
	this->fontResourceID = fontResourceID;
}

const Rectangle<float>& RenderingContextElement::GetSourceRectangle() const noexcept {
	return sourceRectangle;
}

void RenderingContextElement::SetSourceRectangle(const Rectangle<float>& sourceRectangle) noexcept {
	this->sourceRectangle = sourceRectangle;
}

const Vector2<float>& RenderingContextElement::GetPosition() const noexcept {
	return position;
}

void RenderingContextElement::SetPosition(const Vector2<float>& position) noexcept {
	this->position = position;
}

float RenderingContextElement::GetRotation() const noexcept {
	return rotation;
}

void RenderingContextElement::SetRotation(float rotation) noexcept {
	this->rotation = rotation;
}

const string& RenderingContextElement::GetText() const noexcept {
	return text;
}

string& RenderingContextElement::GetText(std::string& result) const {
	return result = text;
}

void RenderingContextElement::SetText(const string& text) {
	this->text = text;
}

void RenderingContextElement::SetText(string&& text) noexcept {
	this->text = text;
}

float RenderingContextElement::GetTextFontSize() const noexcept {
	return textFontSize;
}

void RenderingContextElement::SetTextFontSize(float textFontSize) noexcept {
	this->textFontSize = textFontSize;
}

float RenderingContextElement::GetTextSpacing() const noexcept {
	return textSpacing;
}

void RenderingContextElement::SetTextSpacing(float textSpacing) noexcept {
	this->textSpacing = textSpacing;
}

unsigned int RenderingContextElement::GetLayerIndex() const noexcept {
	return layerIndex;
}

const Vector2<float>& RenderingContextElement::GetSize() const noexcept {
	return size;
}

void RenderingContextElement::SetSize(const Vector2<float>& size) noexcept {
	this->size = size;
}

const Vector2<float>& RenderingContextElement::GetPivot() const noexcept {
	return pivot;
}

void RenderingContextElement::SetPivot(const Vector2<float>& pivot) noexcept {
	this->pivot = pivot;
}

const Color<uint8_t>& RenderingContextElement::GetColor() const noexcept {
	return color;
}

void RenderingContextElement::SetColor(const Color<uint8_t>& color) noexcept {
	this->color = color;
}

void RenderingContextElement::SetLayerIndex(unsigned int layerIndex) noexcept {
	this->layerIndex = layerIndex;
}

RenderingContextElement& RenderingContextElement::operator =(const RenderingContextElement& renderingContextElement) {
	isTexture2DVisible = renderingContextElement.isTexture2DVisible;
	isTextVisible = renderingContextElement.isTextVisible;
	texture2DResourceID = renderingContextElement.texture2DResourceID;
	fontResourceID = renderingContextElement.fontResourceID;
	position = renderingContextElement.position;
	rotation = renderingContextElement.rotation;
	size = renderingContextElement.size;
	pivot = renderingContextElement.pivot;
	color = renderingContextElement.color;
	text = renderingContextElement.text;
	textFontSize = renderingContextElement.textFontSize;
	textSpacing = renderingContextElement.textSpacing;
	layerIndex = renderingContextElement.layerIndex;
	return *this;
}

RenderingContextElement& RenderingContextElement::operator =(RenderingContextElement&& renderingContextElement) noexcept {
	isTexture2DVisible = std::move(renderingContextElement.isTexture2DVisible);
	isTextVisible = std::move(renderingContextElement.isTextVisible);
	texture2DResourceID = std::move(renderingContextElement.texture2DResourceID);
	fontResourceID = std::move(renderingContextElement.fontResourceID);
	position = std::move(renderingContextElement.position);
	rotation = std::move(renderingContextElement.rotation);
	size = std::move(renderingContextElement.size);
	pivot = std::move(renderingContextElement.pivot);
	color = std::move(renderingContextElement.color);
	text = std::move(renderingContextElement.text);
	textFontSize = std::move(renderingContextElement.textFontSize);
	textSpacing = std::move(renderingContextElement.textSpacing);
	layerIndex = std::move(renderingContextElement.layerIndex);
	return *this;
}

bool RenderingContextElement::operator ==(const RenderingContextElement& renderingContextElement) const noexcept {
	return layerIndex == renderingContextElement.layerIndex;
}

bool RenderingContextElement::operator <(const RenderingContextElement& renderingContextElement) const noexcept {
	return layerIndex < renderingContextElement.layerIndex;
}

bool RenderingContextElement::operator <=(const RenderingContextElement& renderingContextElement) const noexcept {
	return layerIndex <= renderingContextElement.layerIndex;
}

bool RenderingContextElement::operator >(const RenderingContextElement& renderingContextElement) const noexcept {
	return layerIndex > renderingContextElement.layerIndex;
}

bool RenderingContextElement::operator >=(const RenderingContextElement& renderingContextElement) const noexcept {
	return layerIndex >= renderingContextElement.layerIndex;
}
