#include <chrono>
#include <memory>
#include <optional>
#include <string>

#include <Klein/Animations/EPlaybackState.hpp>
#include <Klein/Animations/ETimeEvaluationMode.hpp>
#include <Klein/Animations/EvaluatedTimePointIndices.hpp>
#include <Klein/Engine.hpp>
#include <Klein/Math/Rectangle.hpp>
#include <Klein/Math/Vector2.hpp>
#include <Klein/Rendering/Color.hpp>
#include <Klein/ResourceManagement/ResourceID.hpp>
#include <Klein/Scripting/Animations/SpriteAnimatorScript.hpp>
#include <Klein/Scripting/Rendering/SpriteRendererScript.hpp>
#include <Klein/Scripting/Script.hpp>
#include <Klein/SceneManagement/Node.hpp>

using namespace std;
using namespace std::chrono;

using namespace Klein;
using namespace Klein::Animations;
using namespace Klein::Math;
using namespace Klein::Rendering;
using namespace Klein::ResourceManagement;
using namespace Klein::SceneManagement;
using namespace Klein::Scripting;
using namespace Klein::Scripting::Animations;
using namespace Klein::Scripting::Rendering;

SpriteAnimatorScript::SpriteAnimatorScript(Node* node) : Script(node), timeEvaluationMode(ETimeEvaluationMode::Loop), playbackState(EPlaybackState::Playing), startingTime(high_resolution_clock::now()), pausingTime(startingTime) {
	// ...
}

EPlaybackState SpriteAnimatorScript::GetPlaybackState() const noexcept {
	return playbackState;
}

high_resolution_clock::time_point SpriteAnimatorScript::GetStartingTime() const noexcept {
	return startingTime;
}

high_resolution_clock::time_point SpriteAnimatorScript::GetPausingTime() const noexcept {
	return pausingTime;
}

bool SpriteAnimatorScript::PlayAnimation() {
	switch (playbackState) {
	case EPlaybackState::Stopped:
		startingTime = high_resolution_clock::now();
		break;
	case EPlaybackState::Playing:
		return false;
	case EPlaybackState::Paused:
		startingTime = high_resolution_clock::now() - (pausingTime - startingTime);
		break;
	}
	pausingTime = startingTime;
	playbackState = EPlaybackState::Playing;
	return true;
}

bool SpriteAnimatorScript::PauseAnimation() {
	if (playbackState != EPlaybackState::Playing) {
		return false;
	}
	pausingTime = high_resolution_clock::now();
	playbackState = EPlaybackState::Paused;
	UpdateRenderingContext();
	return true;
}

bool SpriteAnimatorScript::StopAnimation() {
	if (playbackState == EPlaybackState::Stopped) {
		return false;
	}
	pausingTime = startingTime;
	playbackState = EPlaybackState::Stopped;
	UpdateRenderingContext();
	return true;
}

bool SpriteAnimatorScript::SynchronizeStartingTime(high_resolution_clock::time_point startingTime) {
	if (playbackState == EPlaybackState::Stopped) {
		return false;
	}
	if (this->startingTime == startingTime) {
		return true;
	}
	this->startingTime = startingTime;
	pausingTime = (pausingTime < startingTime) ? startingTime : pausingTime;
	if (playbackState == EPlaybackState::Paused) {
		UpdateRenderingContext();
	}
	return true;
}

void SpriteAnimatorScript::OnBeforeFrameRender(Engine& engine, const high_resolution_clock::duration& deltaTime) {
	if (playbackState == EPlaybackState::Playing) {
		UpdateRenderingContext();
	}
}

void SpriteAnimatorScript::UpdateRenderingContext() {
	if (shared_ptr<SpriteRendererScript> to_animate_sprite_renderer = toAnimateSpriteRenderer.lock()) {
		high_resolution_clock::duration time_point;
		switch (playbackState) {
		case EPlaybackState::Stopped:
			time_point = high_resolution_clock::duration::zero();
			break;
		case EPlaybackState::Playing:
			time_point = high_resolution_clock::now() - startingTime;
			break;
		case EPlaybackState::Paused:
			time_point = pausingTime - startingTime;
			break;
		}
		if (optional<bool> is_texture_2D_visible = isTexture2DVisibleTimelineRow.GetEvaluatedDiscreteValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetTexture2DVisibility(*is_texture_2D_visible);
		}
		if (optional<bool> is_text_visible = isTextVisibleTimelineRow.GetEvaluatedDiscreteValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetTextVisibility(*is_text_visible);
		}
		if (optional<ResourceID> texture_2d_resource_id = texture2DResourceIDTimelineRow.GetEvaluatedDiscreteValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetTexture2DResourceID(*texture_2d_resource_id);
		}
		if (optional<ResourceID> font_resource_id = fontResourceIDTimelineRow.GetEvaluatedDiscreteValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetFontResourceID(*font_resource_id);
		}
		if (optional<Rectangle<float>> texture_2d_source_rectangle = texture2DSourceRectangleTimelineRow.GetEvaluatedContinousValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetTexture2DSourceRectangle(*texture_2d_source_rectangle);
		}
		if (optional<Vector2<float>> pivot = pivotTimelineRow.GetEvaluatedContinousValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetPivot(*pivot);
		}
		if (optional<Color<float>> color = colorTimelineRow.GetEvaluatedContinousValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetColor(*color);
		}
		if (optional<string> text = textTimelineRow.GetEvaluatedDiscreteValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetText(*text);
		}
		if (optional<float> text_font_size = textFontSizeTimelineRow.GetEvaluatedContinousValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetTextFontSize(*text_font_size);
		}
		if (optional<float> text_spacing = textSpacingTimelineRow.GetEvaluatedContinousValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetTextSpacing(*text_spacing);
		}
		if (optional<unsigned int> layer_index = layerIndexTimelineRow.GetEvaluatedDiscreteValue(time_point, timeEvaluationMode)) {
			to_animate_sprite_renderer->SetLayerIndex(*layer_index);
		}
	}
}
