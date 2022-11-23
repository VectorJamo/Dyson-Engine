#pragma once

#include <iostream>

#ifdef _DEBUG
	#define THROW_ERROR(x) { ThrowError(x, __FILE__, __LINE__); __debugbreak(); }
	#define ASSERT(x) if(!(x)) { Assert(#x, __FILE__, __LINE__); __debugbreak(); }
#else
	#define THROW_ERROR(x) void;
	#define ASSERT(x) void;
#endif

static void ThrowError(const char* message, const char* filePath, int line)
{
	std::cout << "||DEBUG ERROR|| : " << message << std::endl;
	std::cout << "Line: " << line << std::endl;
	std::cout << "File Path: " << filePath << std::endl;
}

static void Assert(const char* expression, const char* filePath, int line)
{
	std::cout << "||ASSERTION FAILED|| : " << "Expression: " << expression << std::endl;
	std::cout << "Line: " << line << std::endl;
	std::cout << "File Path: " << filePath << std::endl;
}