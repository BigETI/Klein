#pragma once

namespace Klein::Animations {

	template <typename TElement>
	struct InterpolatableElement {

		TElement element;

		float easingIn;

		float easingOut;

		bool isLeftBroken;

		bool isRightBroken;
	};
}
