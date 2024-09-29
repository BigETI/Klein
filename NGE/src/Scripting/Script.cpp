#include <chrono>
#include <stdexcept>

#include <NGE/Engine.hpp>
#include <NGE/SceneManagement/Node.hpp>
#include <NGE/Scripting/Script.hpp>

using namespace NGE;
using namespace NGE::SceneManagement;
using namespace NGE::Scripting;
using namespace std;
using namespace std::chrono;

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

void Script::InitializeOrGameTick(Engine& game, high_resolution_clock::duration deltaTime) {
	if (!isInitialized) {
		this->game = &game;
		isInitialized = true;
		OnInitialize(game);
		OnInitialized(game);
		if (isEnabled) {
			OnEnable(game);
			OnEnabled(game);
		}
	}
	if (isEnabled && (this->game == &game)) {
		OnGameTick(game, deltaTime);
		OnGameTicked(game, deltaTime);
	}
}

void Script::InitializeOrBeforeFrameRender(Engine& game, high_resolution_clock::duration deltaTime) {
	if (!isInitialized) {
		this->game = &game;
		isInitialized = true;
		OnInitialize(game);
		OnInitialized(game);
		if (isEnabled) {
			OnEnable(game);
			OnEnabled(game);
		}
	}
	if (isEnabled && (this->game == &game)) {
		OnBeforeFrameRender(game, deltaTime);
		OnBeforeFrameRendered(game, deltaTime);
	}
}

void Script::InitializeOrFrameRender(Engine& game, high_resolution_clock::duration deltaTime) {
	if (!isInitialized) {
		this->game = &game;
		isInitialized = true;
		OnInitialize(game);
		OnInitialized(game);
		if (isEnabled) {
			OnEnable(game);
			OnEnabled(game);
		}
	}
	if (isEnabled && (this->game == &game)) {
		OnFrameRender(game, deltaTime);
		OnFrameRendered(game, deltaTime);
	}
}

void Script::Deinitialize() {
	if (isInitialized) {
		if (isEnabled) {
			isEnabled = false;
			OnDisable(*game);
			OnDisabled(*game);
		}
		isInitialized = false;
		OnDeinitialize(*game);
		OnDeinitialized(*game);
	}
}

void Script::Enable() {
	if (!isEnabled) {
		isEnabled = true;
		if (isInitialized) {
			OnEnable(*game);
			OnEnabled(*game);
		}
	}
}

void Script::Disable() {
	if (isEnabled) {
		isEnabled = false;
		if (isInitialized) {
			OnDisable(*game);
			OnDisabled(*game);
		}
	}
}

void Script::OnInitialize(Engine& game) {
	// ...
}

void Script::OnDeinitialize(Engine& game) {
	// ...
}

void Script::OnEnable(Engine& game) {
	// ...
}

void Script::OnDisable(Engine& game) {
	// ...
}

void Script::OnGameTick(Engine& game, high_resolution_clock::duration deltaTime) {
	// ...
}

void Script::OnBeforeFrameRender(Engine& game, high_resolution_clock::duration deltaTime) {
	// ...
}

void Script::OnFrameRender(Engine& game, high_resolution_clock::duration deltaTime) {
	// ...
}
