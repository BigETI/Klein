#pragma once

#include <chrono>
#include <memory>
#include <string>

#include "../../Animations/ContinuousTimelineRow.hpp"
#include "../../Animations/EPlaybackState.hpp"
#include "../../Animations/ETimeEvaluationMode.hpp"
#include "../../Animations/TimelineRow.hpp"
#include "../../Engine.hpp"
#include "../../Exportables/Exportable.hxx"
#include "../../Math/Rectangle.hpp"
#include "../../Math/Vector2.hpp"
#include "../../Rendering/Color.hpp"
#include "../../ResourceManagement/ResourceID.hpp"
#include "../../SceneManagement/Node.hpp"
#include "../Rendering/SpriteRendererScript.hpp"
#include "../Script.hpp"

namespace Klein::Scripting::Animations {

	class SpriteAnimatorScript : public Klein::Scripting::Script {
	public:

		Klein::Animations::TimelineRow<bool> isTexture2DVisibleTimelineRow;

		Klein::Animations::TimelineRow<bool> isTextVisibleTimelineRow;

		Klein::Animations::TimelineRow<Klein::ResourceManagement::ResourceID> texture2DResourceIDTimelineRow;

		Klein::Animations::TimelineRow<Klein::ResourceManagement::ResourceID> fontResourceIDTimelineRow;

		Klein::Animations::ContinuousTimelineRow<Klein::Math::Rectangle<float>> texture2DSourceRectangleTimelineRow;

		Klein::Animations::ContinuousTimelineRow<Klein::Math::Vector2<float>> pivotTimelineRow;

		Klein::Animations::ContinuousTimelineRow<Klein::Rendering::Color<float>> colorTimelineRow;

		Klein::Animations::TimelineRow<std::string> textTimelineRow;

		Klein::Animations::ContinuousTimelineRow<float> textFontSizeTimelineRow;

		Klein::Animations::ContinuousTimelineRow<float> textSpacingTimelineRow;

		Klein::Animations::TimelineRow<unsigned int> layerIndexTimelineRow;

		std::weak_ptr<Klein::Scripting::Rendering::SpriteRendererScript> toAnimateSpriteRenderer;

		Klein::Animations::ETimeEvaluationMode timeEvaluationMode;

		KLEIN_API SpriteAnimatorScript(Klein::SceneManagement::Node* node);

		KLEIN_API Klein::Animations::EPlaybackState GetPlaybackState() const noexcept;

		KLEIN_API std::chrono::high_resolution_clock::time_point GetStartingTime() const noexcept;

		KLEIN_API std::chrono::high_resolution_clock::time_point GetPausingTime() const noexcept;

		KLEIN_API bool PlayAnimation();

		KLEIN_API bool PauseAnimation();

		KLEIN_API bool StopAnimation();

		KLEIN_API bool SynchronizeStartingTime(std::chrono::high_resolution_clock::time_point startingTime);

	protected:

		KLEIN_API void OnBeforeFrameRender(Klein::Engine& engine, const std::chrono::high_resolution_clock::duration& deltaTime) override;

	private:

		Klein::Animations::EPlaybackState playbackState;

		std::chrono::high_resolution_clock::time_point startingTime;

		std::chrono::high_resolution_clock::time_point pausingTime;

		void UpdateRenderingContext();
	};
}
