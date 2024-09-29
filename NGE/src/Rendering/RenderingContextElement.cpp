#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>

#include <NGE/Math/Vector2.hpp>
#include <NGE/Rendering/Color.hpp>
#include <NGE/Rendering/RenderingContextElement.hpp>
#include <NGE/ResourceManagement/ResourceID.hpp>

using namespace std;

using namespace NGE::Math;
using namespace NGE::Rendering;
using namespace NGE::ResourceManagement;

RenderingContextElement::RenderingContextElement() : rotation(0.0f), layerIndex(0U) {
	// ...
}

RenderingContextElement::RenderingContextElement(
	const ResourceID& resourceID,
	const Rectangle<float>& sourceRectangle,
	const Vector2<float>& position,
	float rotation,
	const Vector2<float>& size,
	const Vector2<float>& pivot,
	const Color<uint8_t>& color,
	unsigned int layerIndex
) :
	resourceID(resourceID),
	sourceRectangle(sourceRectangle),
	position(position),
	rotation(rotation),
	size(size),
	pivot(pivot),
	color(color),
	layerIndex(layerIndex) {
	// ...
}

RenderingContextElement::RenderingContextElement(
	ResourceID&& resourceID,
	Rectangle<float>&& sourceRectangle,
	Vector2<float>&& position,
	float rotation,
	Vector2<float>&& size,
	Vector2<float>&& pivot,
	Color<uint8_t>&& color,
	unsigned int layerIndex
) noexcept :
	resourceID(resourceID),
	sourceRectangle(sourceRectangle),
	position(position),
	rotation(rotation),
	size(size),
	pivot(pivot),
	color(color),
	layerIndex(layerIndex) {
	// ...
}

RenderingContextElement::RenderingContextElement(const RenderingContextElement& renderingContextElement) :
	resourceID(renderingContextElement.resourceID),
	sourceRectangle(renderingContextElement.sourceRectangle),
	position(renderingContextElement.position),
	rotation(renderingContextElement.rotation),
	size(renderingContextElement.size),
	pivot(renderingContextElement.pivot),
	color(renderingContextElement.color),
	layerIndex(renderingContextElement.layerIndex) {
	// ...
}

RenderingContextElement::RenderingContextElement(RenderingContextElement&& renderingContextElement) noexcept :
	resourceID(std::move(renderingContextElement.resourceID)),
	sourceRectangle(std::move(renderingContextElement.sourceRectangle)),
	position(std::move(renderingContextElement.position)),
	rotation(std::move(renderingContextElement.rotation)),
	size(std::move(renderingContextElement.size)),
	pivot(std::move(renderingContextElement.pivot)),
	color(std::move(renderingContextElement.color)),
	layerIndex(std::move(renderingContextElement.layerIndex)) {
	// ...
}

const ResourceID& RenderingContextElement::GetResourceID() const noexcept {
	return resourceID;
}

ResourceID& RenderingContextElement::GetResourceID(ResourceID& result) const {
	return result = resourceID;
}

void RenderingContextElement::SetResourceID(const ResourceID& resourceID) {
	this->resourceID = resourceID;
}

void RenderingContextElement::SetResourceID(ResourceID&& resourceID) noexcept {
	this->resourceID = resourceID;
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
	resourceID = renderingContextElement.resourceID;
	position = renderingContextElement.position;
	rotation = renderingContextElement.rotation;
	size = renderingContextElement.size;
	pivot = renderingContextElement.pivot;
	color = renderingContextElement.color;
	layerIndex = renderingContextElement.layerIndex;
	return *this;
}

RenderingContextElement& RenderingContextElement::operator =(RenderingContextElement&& renderingContextElement) noexcept {
	resourceID = std::move(renderingContextElement.resourceID);
	position = std::move(renderingContextElement.position);
	rotation = std::move(renderingContextElement.rotation);
	size = std::move(renderingContextElement.size);
	pivot = std::move(renderingContextElement.pivot);
	color = std::move(renderingContextElement.color);
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
