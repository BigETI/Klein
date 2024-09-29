#pragma once

#include <memory>
#include <queue>

#include "../Exportables/Exportable.hxx"
#include "../Math/Vector2.hpp"
#include "RenderingContextElement.hpp"

namespace NGE::Rendering {
	class RenderingContext {
	public:

		using ConstantIterator = std::vector<std::shared_ptr<RenderingContextElement>>::const_iterator;
		using Iterator = std::vector<std::shared_ptr<RenderingContextElement>>::iterator;
		using const_iterator = ConstantIterator;
		using iterator = Iterator;

		NGE_API RenderingContext();
		NGE_API RenderingContext(const RenderingContext& renderingContext);
		NGE_API RenderingContext(RenderingContext&& renderingContext) noexcept;

		NGE_API const NGE::Math::Vector2<float>& GetCameraPosition() const noexcept;
		NGE_API void SetCameraPosition(const NGE::Math::Vector2<float>& cameraPosition) noexcept;
		NGE_API float GetCameraRotation() const noexcept;
		NGE_API void SetCameraRotation(float cameraRotation) noexcept;
		NGE_API float GetCameraZoom() const noexcept;
		NGE_API void SetCameraZoom(float cameraZoom) noexcept;
		NGE_API const std::priority_queue<std::shared_ptr<RenderingContextElement>>& GetStagedElements() const noexcept;
		NGE_API std::priority_queue<std::shared_ptr<RenderingContextElement>>& GetStagedElements(
			std::priority_queue<std::shared_ptr<RenderingContextElement>>& result
		) const;
		NGE_API const std::vector<std::shared_ptr<RenderingContextElement>>& GetCommitedElements() const noexcept;
		NGE_API std::vector<std::shared_ptr<RenderingContextElement>>& GetCommitedElements(
			std::vector<std::shared_ptr<RenderingContextElement>>& result
		) const;
		NGE_API void StageElement(const std::shared_ptr<RenderingContextElement>& renderingContextElement);
		NGE_API void StageElement(std::shared_ptr<RenderingContextElement>&& renderingContextElement);
		NGE_API bool TryUnstagingElement(std::shared_ptr<RenderingContextElement>& result) noexcept;
		NGE_API void CommitElements();
		NGE_API void Clear();

		NGE_API const_iterator begin() const;
		NGE_API iterator begin();
		NGE_API const_iterator end() const;
		NGE_API iterator end();

		NGE_API RenderingContext& operator =(const RenderingContext& renderingContext);
		NGE_API RenderingContext& operator =(RenderingContext&& renderingContext) noexcept;

	private:

		NGE::Math::Vector2<float> cameraPosition;
		float cameraRotation;
		float cameraZoom;
		std::priority_queue<std::shared_ptr<RenderingContextElement>> stagedElements;
		std::vector<std::shared_ptr<RenderingContextElement>> commitedElements;
	};
}
