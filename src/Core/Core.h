#pragma once

#ifdef SENGINE_PLATFORM_WINDOWS
	#ifdef SENGINE_BUILD_DLL
		#define SENGINE_API __declspec(dllexport)
    #else
		#define SENGINE_API __declspec(dllimport)
	#endif 
#else
	#error SENGINE IS ONLY SUPPORT WINDOWS
#endif 

#ifdef SENGINE_ASSERT_ENABLE
	#define SENGINE_CORE_ASSERT(x, ...)		{ if (x) { SENGINE_LOG_ERROR("ASSERT ERROR:{0}", __VA_ARGS__);  __debugbreak(); } }
	#define SENGINE_ASSERT(x, ...)			{ if (x) { APPLICATION_LOG_ERROR("ASSERT ERROR:{0}", __VA_ARGS__);  __debugbreak(); } }
#else
	#define SENGINE_CORE_ASSERT(x, ...)	
	#define SENGINE_ASSERT(x, ...)		
#endif
