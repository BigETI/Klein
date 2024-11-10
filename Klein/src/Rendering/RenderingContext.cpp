#include <memory>
#include <queue>
#include <utility>

#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/RenderingContext.hpp>

using namespace std;

using namespace Klein::Math;
using namespace Klein::Rendering;

RenderingContext::RenderingContext() : cameraRotation(0.0f), cameraZoom(1.0f) {
	// ...
}

RenderingContext::RenderingContext(const RenderingContext& renderingContext) :
	cameraPosition(renderingContext.cameraPosition),
	cameraRotation(renderingContext.cameraRotation),
	cameraZoom(renderingContext.cameraZoom),
	stagedElements(renderingContext.stagedElements),
	commitedElements(renderingContext.commitedElements) {
	// ...
}

RenderingContext::RenderingContext(RenderingContext&& renderingContext) noexcept :
	cameraPosition(std::move(renderingContext.cameraPosition)),
	cameraRotation(std::move(renderingContext.cameraRotation)),
	cameraZoom(std::move(renderingContext.cameraZoom)),
	stagedElements(std::move(renderingContext.stagedElements)),
	commitedElements(std::move(renderingContext.commitedElements)) {
	// ...
}

const Vector2<float>& RenderingContext::GetCameraPosition() const noexcept {
	return cameraPosition;
}

void RenderingContext::SetCameraPosition(const Vector2<float>& cameraPosition) noexcept {
	this->cameraPosition = cameraPosition;
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
	cameraPosition = renderingContext.cameraPosition;
	cameraRotation = renderingContext.cameraRotation;
	cameraZoom = renderingContext.cameraZoom;
	stagedElements = renderingContext.stagedElements;
	commitedElements = renderingContext.commitedElements;
	return *this;
}

RenderingContext& RenderingContext::operator =(RenderingContext&& renderingContext) noexcept {
	cameraPosition = std::move(renderingContext.cameraPosition);
	cameraRotation = std::move(renderingContext.cameraRotation);
	cameraZoom = std::move(renderingContext.cameraZoom);
	stagedElements = std::move(renderingContext.stagedElements);
	commitedElements = std::move(renderingContext.commitedElements);
	return *this;
}
