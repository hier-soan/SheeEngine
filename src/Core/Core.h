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

