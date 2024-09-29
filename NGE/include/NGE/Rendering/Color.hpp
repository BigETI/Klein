#pragma once

#include <utility>

namespace NGE::Rendering {
	template <typename TComponent>
	struct Color {

		static_assert(
			std::is_same<char, TComponent>::value ||
			std::is_same<unsigned char, TComponent>::value ||
			std::is_same<short, TComponent>::value ||
			std::is_same<unsigned short, TComponent>::value ||
			std::is_same<int, TComponent>::value ||
			std::is_same<unsigned int, TComponent>::value ||
			std::is_same<long, TComponent>::value ||
			std::is_same<unsigned long, TComponent>::value ||
			std::is_same<long long, TComponent>::value ||
			std::is_same<unsigned long long, TComponent>::value ||
			std::is_same<float, TComponent>::value ||
			std::is_same<double, TComponent>::value ||
			std::is_same<long double, TComponent>::value,
			"The specified color component type must be of a numeric type.");

		TComponent red;
		TComponent green;
		TComponent blue;
		TComponent alpha;

		Color() : red(static_cast<TComponent>(0)), green(static_cast<TComponent>(0)), blue(static_cast<TComponent>(0)), alpha(static_cast<TComponent>(0)) {
			// ...
		}

		Color(TComponent red, TComponent green, TComponent blue) : red(red), green(green), blue(blue), alpha(static_cast<TComponent>(0)) {
			// ...
		}

		Color(TComponent red, TComponent green, TComponent blue, TComponent alpha) : red(red), green(green), blue(blue), alpha(alpha) {
			// ...
		}

		Color(const Color<TComponent>& color) : red(color.red), green(color.green), blue(color.blue), alpha(color.alpha) {
			// ...
		}
		
		Color(Color<TComponent>&& color) : red(std::move(color.red)), green(std::move(color.green)), blue(std::move(color.blue)), alpha(std::move(color.alpha)) {
			// ...
		}
		
		Color<TComponent>& operator =(const Color<TComponent>& color) {
			red = color.red;
			green = color.green;
			blue = color.blue;
			alpha = color.alpha;
			return *this;
		}
		
		Color<TComponent>& operator =(Color<TComponent>&& color) {
			red = std::move(color.red);
			green = std::move(color.green);
			blue = std::move(color.blue);
			alpha = std::move(color.alpha);
			return *this;
		}
	};
}
