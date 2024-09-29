#pragma once

#if defined(IS_NGE_STATIC)
#	define NGE_API
#elif defined(_MSC_VER)
#	if IS_NGE_EXPORTING
#		define NGE_API __declspec(dllexport)
#	else
#		define NGE_API __declspec(dllimport)
#	endif
#elif defined(__GNUC__)
#	if IS_NGE_EXPORTING
#		define NGE_API __attribute__((visibility("default")))
#	else
#		define NGE_API
#	endif
#else
#	define NGE_API
#	if IS_NGE_EXPORTING
#		pragma warning Unknown dynamic link export semantic.
#	else
#		pragma warning Unknown dynamic link import semantic.
#	endif
#endif
