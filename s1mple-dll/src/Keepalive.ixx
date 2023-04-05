module;

#include <ShlObj.h>
#include <thread>
#include <chrono>
#include <stdexcept>

export module Keepalive;

import Keys;

export class Keepalive
{
  static constexpr auto m_subkey = "Software\\s1mple";
  static constexpr auto m_lastSeen = "LastSeen";
  static constexpr auto m_shouldDeload = "ShouldDeload";
  static constexpr auto m_delay = std::chrono::seconds(1);
  static constexpr auto m_terminationKey = Keys::Insert;

  HKEY m_hKey;

public:
  Keepalive() noexcept
  {
    const auto result = RegCreateKeyExA(HKEY_CURRENT_USER, m_subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_hKey, NULL);
    if (result != ERROR_SUCCESS)
    {
      m_hKey = nullptr;
    }
  }

  void run() noexcept
  {
    while (!m_terminationKey.is_currently_pressed())
    {
      try 
      {
        write_registry_qword( m_lastSeen, unix_time());

        bool shouldDeload = read_registry_qword(m_shouldDeload);
        if (shouldDeload)
        {
          shouldDeload = false;
          write_registry_qword(m_shouldDeload, shouldDeload);

          // Exit the loop, this will make the dll deload.
          break;
        }
      }
      catch (const std::runtime_error& err)
      {
        if constexpr (isDebug)
        {
          std::cerr << err.what() << std::endl;
        }
      }

      std::this_thread::sleep_for(m_delay);
    }
  }

  ~Keepalive() noexcept
  {
    if (m_hKey == nullptr)
    {
      return;
    }

    RegCloseKey(m_hKey);
  }

private:
  static uint64_t unix_time() noexcept
  {
    const auto now = std::chrono::system_clock::now();
    const auto unixTime = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    return unixTime;
  }

  void write_registry_qword(std::string_view valueName, uint64_t value)
  {
    const auto result = RegSetValueExA(m_hKey, valueName.data(), 0, REG_QWORD, (BYTE*)&value, sizeof(value));
    if (result != ERROR_SUCCESS)
    {
      throw std::runtime_error("RegSetValueExA has failed!");
    }
  }

  [[nodiscard]] uint64_t read_registry_qword(std::string_view valueName)
  {
    uint64_t dwVal = 0;

    DWORD dwType = REG_QWORD;
    DWORD dwCbData = sizeof(dwVal);

    const auto result = RegQueryValueExA(m_hKey, valueName.data(), NULL, &dwType, (LPBYTE)&dwVal, &dwCbData);
    if (result != ERROR_SUCCESS)
    {
      return -1;
    }

    return dwVal;
  }
};