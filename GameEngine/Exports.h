#pragma once
#if FRANKENGINE_EXPORTS
#define FRANKENGINE_API __declspec(dllexport)
#else
#define FRANKENGINE_API __declspec(dllimport)
#endif