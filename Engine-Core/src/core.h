#pragma once

#ifdef BUILD_DLL
	#define DS __declspec(dllexport)
#elif defined BUILD_EXE
	#define DS __declspec(dllimport)
#endif
