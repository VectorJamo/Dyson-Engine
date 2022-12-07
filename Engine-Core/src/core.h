#pragma once

#ifdef BUILD_DLL
	#define DS __declspec(dllexport)
#else
	#define DS __declspec(dllimport)
#endif
