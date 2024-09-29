#include <chrono>
#include <cstddef>
#include <memory>
#include <numbers>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <NGE/Engine.hpp>
#include <NGE/Math/Vector2.hpp>
#include <NGE/SceneManagement/Node.hpp>
#include <NGE/Scripting/Script.hpp>

using namespace std;
using namespace std::chrono;
using namespace std::numbers;

using namespace NGE;
using namespace NGE::Math;
using namespace NGE::SceneManagement;
using namespace NGE::Scripting;

Node::Node(Node* parent) : parent(parent), isLocallyEnabled(true), isMarkedForDeletion(false), localRotation(0.0f), localScale(1.0f, 1.0f) {
	// ...
}

Node::Node(Node* parent, const string& name) : parent(parent), isLocallyEnabled(true), isMarkedForDeletion(false), name(name), localRotation(0.0f), localScale(1.0f, 1.0f) {
	// ...
}

Node::Node(Node* parent, string&& name) noexcept :
	parent(parent),
	isLocallyEnabled(true),
	isMarkedForDeletion(false),
	name(name),
	localRotation(0.0f),
	localScale(1.0f, 1.0f) {
	// ...
}

Node::~Node() {
	RemoveAllScripts();
	RemoveAllChildren();
}

Node* Node::GetParent() const noexcept {
	return parent;
}

bool Node::IsLocallyEnabled() const noexcept {
	return isLocallyEnabled;
}

bool Node::IsEnabled() const noexcept {
	return isLocallyEnabled && (!parent || parent->IsEnabled());
}

void Node::Enable() {
	if (!isLocallyEnabled) {
		isLocallyEnabled = true;

		// TODO: Notify children and scripts
	}
}

void Node::Disable() {
	if (isLocallyEnabled) {
		isLocallyEnabled = false;

		// TODO: Notify children and scripts
	}
}

bool Node::IsMarkedForDeletion() const noexcept {
	return isMarkedForDeletion;
}

const string& Node::GetName() const noexcept {
	return name;
}

string& Node::GetName(string& result) const {
	return result = name;
}

void Node::SetName(const string& name) {
	this->name = name;
}

void Node::SetName(string&& name) noexcept {
	this->name = std::move(name);
}

const Vector2<float>& Node::GetLocalPosition() const noexcept {
	return localPosition;
}

void Node::SetLocalPosition(const Vector2<float>& localPosition) noexcept {
	this->localPosition = localPosition;
}

Vector2<float> Node::GetPosition() const noexcept {
	Vector2<float> ret;
	const Node* parent(GetParent());
	if (parent) {
		float phi(parent->GetRotation() * pi_v<float> / 180.0f);
		Vector2<float> scaled_position(localPosition * parent->GetScale());
		ret = parent->GetPosition() + Vector2<float>((cosf(phi) * scaled_position.x) - (sinf(phi) * scaled_position.y), (sinf(phi) * scaled_position.x) + (cosf(phi) * scaled_position.y));
	}
	else {
		ret = localPosition;
	}
	return ret;
}

//void Node::SetPosition(const Vector2<float>& position) noexcept {
	// TODO: Implement set absolute position
//}

float Node::GetLocalRotation() const noexcept {
	return localRotation;
}

void Node::SetLocalRotation(float localRotation) noexcept {
	this->localRotation = localRotation;
	while (this->localRotation >= 360.0f) {
		this->localRotation -= 360.0f;
	}
	while (this->localRotation < 0.0f) {
		this->localRotation += 360.0f;
	}
}

float Node::GetRotation() const noexcept {
	float ret(localRotation);
	const Node* node(GetParent());
	while (node) {
		ret += node->localRotation;
		node = node->GetParent();
	}
	return ret;
}

void Node::SetRotation(float rotation) noexcept {
	const Node* parent(GetParent());
	if (parent) {
		SetLocalRotation(rotation - parent->GetRotation());
	}
	else {
		SetLocalRotation(rotation);
	}
}

const Vector2<float>& Node::GetLocalScale() const noexcept {
	return localScale;
}

void Node::SetLocalScale(const Vector2<float>& localScale) noexcept {
	this->localScale = localScale;
}

Vector2<float> Node::GetScale() const noexcept {
	Vector2<float> ret(localScale);
	const Node* node(GetParent());
	while (node) {
		ret *= node->localScale;
		node = node->GetParent();
	}
	return ret;
}

void Node::SetScale(const Vector2<float>& scale) noexcept {
	const Node* parent(GetParent());
	if (parent) {
		Vector2<float> parent_scale(parent->GetScale());
		localScale = Vector2<float>(
			(abs(parent_scale.x) > numeric_limits<float>::epsilon()) ? (scale.x / parent_scale.x) : localScale.x,
			(abs(parent_scale.y) > numeric_limits<float>::epsilon()) ? (scale.y / parent_scale.y) : localScale.y
		);
	}
	else {
		localScale = scale;
	}
}

const vector<shared_ptr<Node>>& Node::GetChildren() const noexcept {
	return children;
}

vector<shared_ptr<Node>>& Node::GetChildren(vector<shared_ptr<Node>>& result) const {
	return result = children;
}

shared_ptr<Node> Node::CreateNewChild() {
	shared_ptr<Node> ret(make_shared<Node>(this));
	children.push_back(ret);
	OnChildAdded(ret);
	return ret;
}

shared_ptr<Node> Node::CreateNewChild(const string& name) {
	shared_ptr<Node> ret(make_shared<Node>(this, name));
	children.push_back(ret);
	OnChildAdded(ret);
	return ret;
}

shared_ptr<Node> Node::CreateNewChild(string&& name) {
	shared_ptr<Node> ret(make_shared<Node>(this, std::move(name)));
	children.push_back(ret);
	OnChildAdded(ret);
	return ret;
}

shared_ptr<Node> Node::CreateNewAndInsertChild(size_t index) {
	if (index > children.size()) {
		throw out_of_range("Specified index is out of range.");
	}
	shared_ptr<Node> ret(make_shared<Node>(this));
	children.insert(children.begin() + index, ret);
	OnChildAdded(ret);
	return ret;
}

shared_ptr<Node> Node::CreateNewAndInsertChild(size_t index, const string& name) {
	if (index > children.size()) {
		throw out_of_range("Specified index is out of range.");
	}
	shared_ptr<Node> ret(make_shared<Node>(this, name));
	children.insert(children.begin() + index, ret);
	OnChildAdded(ret);
	return ret;
}

shared_ptr<Node> Node::CreateNewAndInsertChild(size_t index, string&& name) {
	if (index > children.size()) {
		throw out_of_range("Specified index is out of range.");
	}
	shared_ptr<Node> ret(make_shared<Node>(this, std::move(name)));
	children.insert(children.begin() + index, ret);
	OnChildAdded(ret);
	return ret;
}

bool Node::RemoveChild(size_t index) {
	bool ret(index < children.size());
	if (ret) {
		shared_ptr<Node> child(children.at(index));
		children.erase(children.begin() + index);
		OnChildRemoved(child);
	}
	return ret;
}

bool Node::RemoveChild(std::shared_ptr<Node> child) {
	const auto& found_child_it(std::find(children.begin(), children.end(), child));
	bool ret(found_child_it != children.end());
	if (ret) {
		children.erase(found_child_it);
		OnChildRemoved(child);
	}
	return ret;
}

void Node::RemoveAllChildren() noexcept {
	if (OnChildRemoved.IsEmpty()) {
		children.clear();
	}
	else {
		vector<shared_ptr<Node>> children(this->children);
		this->children.clear();
		for (const auto& child : children) {
			OnChildRemoved(child);
		}
	}
}

const vector<shared_ptr<Script>>& Node::GetScripts() const noexcept {
	return scripts;
}

vector<shared_ptr<Script>>& Node::GetScripts(vector<shared_ptr<Script>>& result) const {
	return result = scripts;
}

void Node::RemoveAllScripts() {
	for (auto& script : scripts) {
		OnScriptRemoved(script);
		script->Deinitialize();
	}
	scripts.clear();
}

void Node::GameTickScripts(Engine& engine, high_resolution_clock::duration deltaTime) {
	if (isMarkedForDeletion) {
		for (auto child : children) {
			child->Destroy();
		}
	}
	if (isLocallyEnabled) {
		for (auto child : children) {
			child->GameTickScripts(engine, deltaTime);
		}
	}
	if (isMarkedForDeletion) {
		for (auto script : scripts) {
			OnScriptRemoved(script);
			script->Deinitialize();
		}
		scripts.clear();
		children.clear();
	}
	else if (isLocallyEnabled) {
		temporaryScripts = scripts;
		for (auto script : temporaryScripts) {
			script->InitializeOrGameTick(engine, deltaTime);
		}
		temporaryScripts.clear();
	}
}

void Node::BeforeFrameRenderScripts(Engine& engine, high_resolution_clock::duration deltaTime) {
	if (isMarkedForDeletion) {
		for (auto child : children) {
			child->Destroy();
		}
	}
	if (isLocallyEnabled) {
		for (auto child : children) {
			child->BeforeFrameRenderScripts(engine, deltaTime);
		}
	}
	if (isMarkedForDeletion) {
		for (auto script : scripts) {
			OnScriptRemoved(script);
			script->Deinitialize();
		}
		scripts.clear();
		children.clear();
	}
	else if (isLocallyEnabled) {
		temporaryScripts = scripts;
		for (auto script : temporaryScripts) {
			script->InitializeOrBeforeFrameRender(engine, deltaTime);
		}
		temporaryScripts.clear();
	}
}

void Node::FrameRenderScripts(Engine& engine, high_resolution_clock::duration deltaTime) {
	if (isMarkedForDeletion) {
		for (auto child : children) {
			child->Destroy();
		}
	}
	if (isLocallyEnabled) {
		for (auto child : children) {
			child->FrameRenderScripts(engine, deltaTime);
		}
	}
	if (isMarkedForDeletion) {
		for (auto script : scripts) {
			OnScriptRemoved(script);
			script->Deinitialize();
		}
		scripts.clear();
		children.clear();
	}
	else if (isLocallyEnabled) {
		temporaryScripts = scripts;
		for (auto script : temporaryScripts) {
			script->InitializeOrFrameRender(engine, deltaTime);
		}
		temporaryScripts.clear();
	}
}

void Node::Destroy() {
	isMarkedForDeletion = true;
}
