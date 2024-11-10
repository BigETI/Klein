#pragma once

#if defined(IS_KLEIN_STATIC)
#	define KLEIN_API
#elif defined(_MSC_VER)
#	if IS_KLEIN_EXPORTING
#		define KLEIN_API __declspec(dllexport)
#	else
#		define KLEIN_API __declspec(dllimport)
#	endif
#elif defined(__GNUC__)
#	if IS_KLEIN_EXPORTING
#		define KLEIN_API __attribute__((visibility("default")))
#	else
#		define KLEIN_API
#	endif
#else
#	define KLEIN_API
#	if IS_KLEIN_EXPORTING
#		pragma warning Unknown dynamic link export semantic.
#	else
#		pragma warning Unknown dynamic link import semantic.
#	endif
#endif
