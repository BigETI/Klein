#include <chrono>
#include <stdexcept>

#include <NGE/Engine.hpp>
#include <NGE/SceneManagement/Node.hpp>
#include <NGE/Scripting/Script.hpp>

using namespace std;
using namespace std::chrono;

using namespace NGE;
using namespace NGE::SceneManagement;
using namespace NGE::Scripting;

Script::Script(Node* node) : isInitialized(false), isEnabled(true), node(node) {
	if (!node) {
		throw invalid_argument("Specified node is null.");
	}
}

Script::~Script() noexcept {
	Deinitialize();
}

bool Script::IsInitialized() const noexcept {
	return isInitialized;
}

bool Script::IsEnabled() const noexcept {
	return isEnabled;
}

void Script::SetEnabledState(bool enabledState) noexcept {
	isEnabled = enabledState;
}

const Node& Script::GetNode() const noexcept {
	return *node;
}

Node& Script::GetNode() noexcept {
	return *node;
}

void Script::InitializeOrGameTick(Engine& engine, high_resolution_clock::duration deltaTime) {
	if (!isInitialized) {
		this->engine = &engine;
		isInitialized = true;
		OnInitialize(engine);
		OnInitialized(engine);
		if (isEnabled) {
			OnEnable(engine);
			OnEnabled(engine);
		}
	}
	if (isEnabled && (this->engine == &engine)) {
		OnGameTick(engine, deltaTime);
		OnGameTicked(engine, deltaTime);
	}
}

void Script::InitializeOrBeforeFrameRender(Engine& engine, high_resolution_clock::duration deltaTime) {
	if (!isInitialized) {
		this->engine = &engine;
		isInitialized = true;
		OnInitialize(engine);
		OnInitialized(engine);
		if (isEnabled) {
			OnEnable(engine);
			OnEnabled(engine);
		}
	}
	if (isEnabled && (this->engine == &engine)) {
		OnBeforeFrameRender(engine, deltaTime);
		OnBeforeFrameRendered(engine, deltaTime);
	}
}

void Script::InitializeOrFrameRender(Engine& engine, high_resolution_clock::duration deltaTime) {
	if (!isInitialized) {
		this->engine = &engine;
		isInitialized = true;
		OnInitialize(engine);
		OnInitialized(engine);
		if (isEnabled) {
			OnEnable(engine);
			OnEnabled(engine);
		}
	}
	if (isEnabled && (this->engine == &engine)) {
		OnFrameRender(engine, deltaTime);
		OnFrameRendered(engine, deltaTime);
	}
}

void Script::Deinitialize() {
	if (isInitialized) {
		if (isEnabled) {
			isEnabled = false;
			OnDisable(*engine);
			OnDisabled(*engine);
		}
		isInitialized = false;
		OnDeinitialize(*engine);
		OnDeinitialized(*engine);
	}
}

void Script::Enable() {
	if (!isEnabled) {
		isEnabled = true;
		if (isInitialized) {
			OnEnable(*engine);
			OnEnabled(*engine);
		}
	}
}

void Script::Disable() {
	if (isEnabled) {
		isEnabled = false;
		if (isInitialized) {
			OnDisable(*engine);
			OnDisabled(*engine);
		}
	}
}

void Script::OnInitialize(Engine& engine) {
	// ...
}

void Script::OnDeinitialize(Engine& engine) {
	// ...
}

void Script::OnEnable(Engine& engine) {
	// ...
}

void Script::OnDisable(Engine& engine) {
	// ...
}

void Script::OnGameTick(Engine& engine, high_resolution_clock::duration deltaTime) {
	// ...
}

void Script::OnBeforeFrameRender(Engine& engine, high_resolution_clock::duration deltaTime) {
	// ...
}

void Script::OnFrameRender(Engine& engine, high_resolution_clock::duration deltaTime) {
	// ...
}
