#pragma once

#include <functional>

namespace Klein {
	template <typename TReturn, typename... TArguments>
	struct Delegate {
		using ReturnType = TReturn;
		using StandardFunction = std::function<TReturn(TArguments...)>;
		using ConstantStandardFunctionReference = const std::function<TReturn(TArguments...)>&;
		using MovableStandardFunctionReference = std::function<TReturn(TArguments...)>&&;
		using FunctionReference = TReturn(&)(TArguments...);
		using ConstantFunctionReference = const TReturn(&)(TArguments...);
		using FunctionPointer = TReturn(*)(TArguments...);
		using ConstantFunctionPointer = const TReturn(*)(TArguments...);

		Delegate() = delete;
		Delegate(const Delegate&) = delete;
		Delegate(Delegate&&) = delete;
		Delegate& operator =(const Delegate&) = delete;
		Delegate& operator =(Delegate&&) = delete;
	};
}
