#pragma once

#include <memory>
#include <queue>

#include "../Exportables/Exportable.hxx"
#include "../Math/Vector2.hpp"
#include "RenderingContextElement.hpp"

namespace Klein::Rendering {
	class RenderingContext {
	public:

		using ConstantIterator = std::vector<std::shared_ptr<RenderingContextElement>>::const_iterator;
		using Iterator = std::vector<std::shared_ptr<RenderingContextElement>>::iterator;
		using const_iterator = ConstantIterator;
		using iterator = Iterator;

		KLEIN_API RenderingContext();
		KLEIN_API RenderingContext(const RenderingContext& renderingContext);
		KLEIN_API RenderingContext(RenderingContext&& renderingContext) noexcept;

		KLEIN_API const Klein::Math::Vector2<float>& GetCameraPosition() const noexcept;
		KLEIN_API void SetCameraPosition(const Klein::Math::Vector2<float>& cameraPosition) noexcept;
		KLEIN_API float GetCameraRotation() const noexcept;
		KLEIN_API void SetCameraRotation(float cameraRotation) noexcept;
		KLEIN_API float GetCameraZoom() const noexcept;
		KLEIN_API void SetCameraZoom(float cameraZoom) noexcept;
		KLEIN_API const std::priority_queue<std::shared_ptr<RenderingContextElement>>& GetStagedElements() const noexcept;
		KLEIN_API std::priority_queue<std::shared_ptr<RenderingContextElement>>& GetStagedElements(
			std::priority_queue<std::shared_ptr<RenderingContextElement>>& result
		) const;
		KLEIN_API const std::vector<std::shared_ptr<RenderingContextElement>>& GetCommitedElements() const noexcept;
		KLEIN_API std::vector<std::shared_ptr<RenderingContextElement>>& GetCommitedElements(
			std::vector<std::shared_ptr<RenderingContextElement>>& result
		) const;
		KLEIN_API void StageElement(const std::shared_ptr<RenderingContextElement>& renderingContextElement);
		KLEIN_API void StageElement(std::shared_ptr<RenderingContextElement>&& renderingContextElement);
		KLEIN_API bool TryUnstagingElement(std::shared_ptr<RenderingContextElement>& result) noexcept;
		KLEIN_API void CommitElements();
		KLEIN_API void Clear();

		KLEIN_API const_iterator begin() const;
		KLEIN_API iterator begin();
		KLEIN_API const_iterator end() const;
		KLEIN_API iterator end();

		KLEIN_API RenderingContext& operator =(const RenderingContext& renderingContext);
		KLEIN_API RenderingContext& operator =(RenderingContext&& renderingContext) noexcept;

	private:

		Klein::Math::Vector2<float> cameraPosition;
		float cameraRotation;
		float cameraZoom;
		std::priority_queue<std::shared_ptr<RenderingContextElement>> stagedElements;
		std::vector<std::shared_ptr<RenderingContextElement>> commitedElements;
	};
}
