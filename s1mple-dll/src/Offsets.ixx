module;

#include <TlHelp32.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <unordered_map>
#include <map>
#include <string>

export module Offsets;

struct OffsetsValues
{
  uint64_t
    timestamp;
  ptrdiff_t
    client = 0,
    engine = 0;
  std::map<const std::string, ptrdiff_t>
    signatures,
    netvars;
};

export class Offsets
{
  static OffsetsValues offsetsValues;

public:
  static const OffsetsValues& values;

  static void load()
  {
    try 
    {
      load_dump();
      load_modules();
    }
    catch (const std::exception& ex)
    {
      if constexpr (isDebug)
      {
        fputs("Offsets::load() failed!", stderr);
      }

      throw ex;
    }
  }

private:
  static void load_dump()
  {
    const auto json = fetch_dump();

    offsetsValues.timestamp = json["timestamp"].get<uint64_t>();
    for (auto& [key, val] : json["signatures"].items())
    {
      offsetsValues.signatures[key] = val;
    }

    for (auto& [key, val] : json["netvars"].items())
    {
      offsetsValues.netvars[key] = val;
    }

    if constexpr (isDebug)
    {
      puts(std::format("timestamp: {}", offsetsValues.timestamp).c_str());
      puts("signatures:");
      for (const auto& [key, value] : offsetsValues.signatures)
      {
        puts(std::format("  {}: {}", key, value).c_str());
      }

      puts("netvars:");
      for (const auto& [key, value] : offsetsValues.netvars)
      {
        puts(std::format("  {}: {}", key, value).c_str());
      }
    }
  }

  static void load_modules()
  {
    if constexpr (isTesting)
    {
      return;
    }

    try 
    {
      const auto pid = GetCurrentProcessId();
      offsetsValues.client = load_module("client.dll", pid);
      offsetsValues.engine = load_module("engine.dll", pid);

      if constexpr (isDebug)
      {
        puts("Loaded modules!");
      }
    }
    catch (const std::exception& ex)
    {
      if constexpr (isDebug)
      {
        fputs("Offsets::load_modules() failed!", stderr);
      }
      
      throw ex;
    }
  }

  static nlohmann::json fetch_dump()
  {
    constexpr auto url = "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json";

    auto fetchResponse = cpr::Get(cpr::Url{ url });
    if (fetchResponse.error)
    {
      if constexpr (isDebug)
      {
        fputs(std::format("Offsets::fetch_dump() failed: {}", fetchResponse.error.message).c_str(), stderr);
      }

      throw std::exception();
    }

    return nlohmann::json::parse(fetchResponse.text);
  }

  static [[nodiscard]] ptrdiff_t load_module(std::string_view name, DWORD pid)
  {
    HMODULE hModule = nullptr;

    auto check_module = [&](HANDLE hSnapshot, PMODULEENTRY32 pModuleEntry)
    {
      if (!strcmp(pModuleEntry->szModule, name.data()))
      {
        CloseHandle(hSnapshot);
        hModule = pModuleEntry->hModule;
      }
    };

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    MODULEENTRY32 moduleEntry =
    {
      .dwSize = sizeof(MODULEENTRY32),
    };

    // Load the first module in the system.
    if (Module32First(hSnapshot, &moduleEntry))
    {
      // Is it this one?
      check_module(hSnapshot, &moduleEntry);

      // Iterate over all of the other modules in the system.
      while (Module32Next(hSnapshot, &moduleEntry) && !hModule)
      {
        check_module(hSnapshot, &moduleEntry);
      }
    }

    if (hModule == nullptr)
    {
      if constexpr (isDebug)
      {
        fputs(std::format("Offsets::load_module() failed: Can't find a module named '{}'!", name).c_str(), stderr);
      }

      throw std::exception();
    }

    auto moduleAddress = reinterpret_cast<ptrdiff_t>(hModule);
    if constexpr (isDebug)
    {
      puts(std::format("Loaded module \"{}\" at 0x{:X}", name, moduleAddress).c_str());
    }

    return moduleAddress;
  }
};

OffsetsValues Offsets::offsetsValues;
const OffsetsValues& Offsets::values = offsetsValues;
