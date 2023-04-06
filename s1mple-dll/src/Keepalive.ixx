module;

#include <ShlObj.h>
#include <thread>
#include <chrono>

export module Keepalive;

import Keys;

export class Keepalive
{
  static constexpr auto subkey = "Software\\s1mple";
  static constexpr auto lastSeen = "LastSeen";
  static constexpr auto shouldDeload = "ShouldDeload";
  static constexpr auto delay = std::chrono::seconds(1);
  static constexpr auto terminationKey = Keys::Insert;

  static HKEY hKey;
  static std::atomic<bool> isAlive;

public:
  static void run() noexcept
  {
    isAlive = true;

    const auto result = RegCreateKeyExA(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
    if (result != ERROR_SUCCESS)
    {
      if constexpr (isDebug)
      {
        fputs("Keepalive::run() failed to open registry, continuing without it!", stderr);
      }

      hKey = nullptr;
    }

    while (!terminationKey.is_currently_pressed())
    {
      try
      {
        write_registry_qword(lastSeen, unix_time());

        auto b_shouldDeload = read_registry_qword(shouldDeload);
        if (b_shouldDeload)
        {
          b_shouldDeload = false;
          write_registry_qword(shouldDeload, b_shouldDeload);

          // Exit the loop, this will make the dll deload.
          break;
        }
      }
      catch (const std::runtime_error& err)
      {
        if constexpr (isDebug)
        {
          fputs(err.what(), stderr);
        }
      }

      std::this_thread::sleep_for(delay);
    }

    if (hKey != nullptr)
    {
      RegCloseKey(hKey);
    }

    isAlive = false;
  }

  [[nodiscard]] static bool is_alive() noexcept
  {
    return isAlive;
  }

private:
  static uint64_t unix_time() noexcept
  {
    const auto now = std::chrono::system_clock::now();
    const auto unixTime = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    return unixTime;
  }

  static void write_registry_qword(std::string_view valueName, uint64_t value)
  {
    const auto result = RegSetValueExA(hKey, valueName.data(), 0, REG_QWORD, (BYTE*)&value, sizeof(value));
    if (result != ERROR_SUCCESS)
    {
      if constexpr (isDebug)
      {
        fputs(std::format("Keepalive::write_registry_qword({}, {}) failed!", valueName, value).c_str(), stderr);
      }

      throw std::exception();
    }
  }

  static [[nodiscard]] uint64_t read_registry_qword(std::string_view valueName)
  {
    uint64_t dwVal = 0;

    DWORD dwType = REG_QWORD;
    DWORD dwCbData = sizeof(dwVal);

    const auto result = RegQueryValueExA(hKey, valueName.data(), NULL, &dwType, (LPBYTE)&dwVal, &dwCbData);
    if (result != ERROR_SUCCESS)
    {
      if constexpr (isDebug)
      {
        fputs(std::format("Keepalive::read_registry_qword({}) failed!", valueName).c_str(), stderr);
      }

      throw std::exception();
    }

    return dwVal;
  }
};

HKEY Keepalive::hKey;
std::atomic<bool> Keepalive::isAlive = true;