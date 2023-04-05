#pragma once

#ifdef TESTING
constexpr auto isTesting = true;
#else
constexpr auto isTesting = false;
#endif

#ifdef _DEBUG
constexpr auto isDebug = true;
constexpr auto isRelease = false;

#include <iostream>
#else
constexpr auto isDebug = false;
constexpr auto isRelease = true;
#endif

#include <Windows.h>
