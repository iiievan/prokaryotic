#pragma once

#ifdef PRKRTC_PLATFORM_WINDOWS
	#ifdef PRKRTC_BUILD_DLL
		#define PRKRTC_API __declspec(dllexport)
	#else
		#define PRKRTC_API __declspec(dllimport)
	#endif
#else
	#error Procaryotic engine support only Windows!
#endif

#ifdef PRKRTC_DEBUG
	#define PRKRTC_ENABLE_ASSERTS
#endif

#ifdef PRKRTC_ENABLE_ASSERTS
	#define PRKRTC_ASSERT(x, ...) { if(!(x)) { LOG_CLIENT_ERR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PRKRTC_CORE_ASSERT(x, ...) { if(!(x)) { LOG_CORE_ERR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PRKRTC_ASSERT(x, ...)
	#define PRKRTC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
