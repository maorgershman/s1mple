#pragma once

#ifdef TESTING
constexpr auto isTesting = true;
#else
constexpr auto isTesting = false;
#endif

#ifdef _DEBUG
constexpr auto isDebug = true;
constexpr auto isRelease = false;
#pragma comment (lib, "libcurl-d.lib")
#else
constexpr auto isDebug = false;
constexpr auto isRelease = true;
#pragma comment (lib, "libcurl.lib")
#endif

#pragma comment (lib, "cpr.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")

#include <Windows.h>
#include <iostream>
#include <format>

template<typename T>
static inline [[nodiscard]] T read_memory(ptrdiff_t address) noexcept
{
  T buffer{};
  if constexpr (isTesting)
  {
    return buffer;
  }

  memcpy(&buffer, reinterpret_cast<const void*>(address), sizeof(buffer));
  return buffer;
}

template<typename T>
static inline void write_memory(ptrdiff_t address, T value) noexcept
{
  if constexpr (isTesting)
  {
    return;
  }

  memcpy(reinterpret_cast<void*>(address), &value, sizeof(value));
}