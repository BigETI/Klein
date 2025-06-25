#include <memory>
#include <queue>
#include <utility>

#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/RenderingContext.hpp>

using namespace std;

using namespace Klein::Math;
using namespace Klein::Rendering;

RenderingContext::RenderingContext() : isClearingBackground(false), cameraAlignment(0.5f, 0.5f), cameraRotation(0.0f), cameraZoom(1.0f) {
	// ...
}

RenderingContext::RenderingContext(const RenderingContext& renderingContext) :
	isClearingBackground(renderingContext.isClearingBackground),
	clearBackgroundColor(renderingContext.clearBackgroundColor),
	cameraPosition(renderingContext.cameraPosition),
	cameraAlignment(renderingContext.cameraAlignment),
	cameraRotation(renderingContext.cameraRotation),
	cameraZoom(renderingContext.cameraZoom),
	stagedElements(renderingContext.stagedElements),
	commitedElements(renderingContext.commitedElements) {
	// ...
}

RenderingContext::RenderingContext(RenderingContext&& renderingContext) noexcept :
	isClearingBackground(std::move(renderingContext.isClearingBackground)),
	clearBackgroundColor(std::move(renderingContext.clearBackgroundColor)),
	cameraPosition(std::move(renderingContext.cameraPosition)),
	cameraAlignment(std::move(renderingContext.cameraAlignment)),
	cameraRotation(std::move(renderingContext.cameraRotation)),
	cameraZoom(std::move(renderingContext.cameraZoom)),
	stagedElements(std::move(renderingContext.stagedElements)),
	commitedElements(std::move(renderingContext.commitedElements)) {
	// ...
}

bool RenderingContext::IsClearingBackground() const noexcept {
	return isClearingBackground;
}

void RenderingContext::SetClearingBackgroundState(bool isClearingBackground) noexcept {
	this->isClearingBackground = isClearingBackground;
}

const Color<float>& RenderingContext::GetClearBackgroundColor() const noexcept {
	return clearBackgroundColor;
}

void RenderingContext::SetClearBackgroundColor(const Color<float>& clearBackgroundColor) noexcept {
	this->clearBackgroundColor = clearBackgroundColor;
}

const Vector2<float>& RenderingContext::GetCameraPosition() const noexcept {
	return cameraPosition;
}

void RenderingContext::SetCameraPosition(const Vector2<float>& cameraPosition) noexcept {
	this->cameraPosition = cameraPosition;
}

const Vector2<float>& RenderingContext::GetCameraAlignment() const noexcept {
	return cameraAlignment;
}

void RenderingContext::SetCameraAlignment(const Vector2<float>& cameraAlignment) noexcept {
	this->cameraAlignment = cameraAlignment;
}

float RenderingContext::GetCameraRotation() const noexcept {
	return cameraRotation;
}

void RenderingContext::SetCameraRotation(float cameraRotation) noexcept {
	this->cameraRotation = cameraRotation;
}

float RenderingContext::GetCameraZoom() const noexcept {
	return cameraZoom;
}

void RenderingContext::SetCameraZoom(float cameraZoom) noexcept {
	this->cameraZoom = cameraZoom;
}

const priority_queue<shared_ptr<RenderingContextElement>>& RenderingContext::GetStagedElements() const noexcept {
	return stagedElements;
}

priority_queue<shared_ptr<RenderingContextElement>>& RenderingContext::GetStagedElements(priority_queue<shared_ptr<RenderingContextElement>>& result) const {
	return result = stagedElements;
}

const vector<shared_ptr<RenderingContextElement>>& RenderingContext::GetCommitedElements() const noexcept {
	return commitedElements;
}

vector<shared_ptr<RenderingContextElement>>& RenderingContext::GetCommitedElements(std::vector<shared_ptr<RenderingContextElement>>& result) const {
	return result = commitedElements;
}

void RenderingContext::StageElement(const shared_ptr<RenderingContextElement>& renderingContextElement) {
	stagedElements.push(renderingContextElement);
}

void RenderingContext::StageElement(shared_ptr<RenderingContextElement>&& renderingContextElement) {
	stagedElements.push(renderingContextElement);
}

bool RenderingContext::TryUnstagingElement(shared_ptr<RenderingContextElement>& result) noexcept {
	bool ret(!stagedElements.empty());
	if (ret) {
		result = stagedElements.top();
		stagedElements.pop();
	}
	return ret;
}

void RenderingContext::CommitElements() {
	while (!stagedElements.empty()) {
		commitedElements.push_back(stagedElements.top());
		stagedElements.pop();
	}
}

void RenderingContext::Clear() {
	while (!stagedElements.empty()) {
		stagedElements.pop();
	}
	commitedElements.clear();
}

RenderingContext::const_iterator RenderingContext::begin() const {
	return commitedElements.begin();
}

RenderingContext::iterator RenderingContext::begin() {
	return commitedElements.begin();
}

RenderingContext::const_iterator RenderingContext::end() const {
	return commitedElements.end();
}

RenderingContext::iterator RenderingContext::end() {
	return commitedElements.end();
}

RenderingContext& RenderingContext::operator =(const RenderingContext& renderingContext) {
	isClearingBackground = renderingContext.isClearingBackground;
	clearBackgroundColor = renderingContext.clearBackgroundColor;
	cameraPosition = renderingContext.cameraPosition;
	cameraAlignment = renderingContext.cameraAlignment;
	cameraRotation = renderingContext.cameraRotation;
	cameraZoom = renderingContext.cameraZoom;
	stagedElements = renderingContext.stagedElements;
	commitedElements = renderingContext.commitedElements;
	return *this;
}

RenderingContext& RenderingContext::operator =(RenderingContext&& renderingContext) noexcept {
	isClearingBackground = std::move(renderingContext.isClearingBackground);
	clearBackgroundColor = std::move(renderingContext.clearBackgroundColor);
	cameraPosition = std::move(renderingContext.cameraPosition);
	cameraAlignment = std::move(renderingContext.cameraAlignment);
	cameraRotation = std::move(renderingContext.cameraRotation);
	cameraZoom = std::move(renderingContext.cameraZoom);
	stagedElements = std::move(renderingContext.stagedElements);
	commitedElements = std::move(renderingContext.commitedElements);
	return *this;
}
