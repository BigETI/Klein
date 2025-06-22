#pragma once

#include "./Node.hpp"

namespace Klein::SceneManagement {
	class Node;

	class ISceneLoader {
	public:

		ISceneLoader() {
			// ...
		}

		ISceneLoader(const ISceneLoader&) = delete;
		ISceneLoader(ISceneLoader&&) noexcept = delete;

		virtual ~ISceneLoader() noexcept {
			// ...
		}

		virtual void Load(Node& rootNode) = 0;

		ISceneLoader& operator =(const ISceneLoader&) = delete;
		ISceneLoader& operator =(ISceneLoader&&) noexcept = delete;
	};
}
