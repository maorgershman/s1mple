#include "nlohmann\json.hpp"

export module Config;

import Keys;
import Utils;

struct Config
{
    Key terminationKey;
    std::chrono::high_resolution_clock::duration ingameTickDelay;
    std::chrono::high_resolution_clock::duration standbyTickDelay;
    bool isOverlayAllowed;
};

constexpr Config defaultConfig =
{
    .terminationKey = Keys::Insert,
    .ingameTickDelay = std::chrono::milliseconds(1),
    .standbyTickDelay = std::chrono::milliseconds(10),
    .isOverlayAllowed = true
};

// Wrapper class for config management using singleton
export class ConfigWrapper
{
    Config load_config() const
    {
        const auto path = std::format(L"{}\\config.json", Utils::get_data_folder_path());

        auto config = defaultConfig;
        try
        { // Attempt to load the data from the config
            WPRINT(std::format(L"Loading config from {}", path));

            const auto jConfig = nlohmann::json::parse(std::ifstream(path));

            config.terminationKey = Keys::from_string(jConfig["TerminationKey"].get<std::string_view>()).value();
            config.ingameTickDelay = std::chrono::milliseconds(jConfig["IngameTickDelay"].get<int>());
            config.standbyTickDelay = std::chrono::milliseconds(jConfig["StandbyTickDelay"].get<int>());
            config.isOverlayAllowed = jConfig["IsOverlayAllowed"].get<bool>();

            PRINT("Loaded config successfully!");
        }
        catch (...)
        { // If failed, load the default config and save it to the disk
            PRINT("Failed to load the config, loading and saving default one instead.");

            // Revert the default config
            config = defaultConfig;

            nlohmann::json jConfig;
            jConfig["TerminationKey"] = config.terminationKey.description;
            jConfig["IngameTickDelay"] = std::chrono::duration_cast<std::chrono::milliseconds>(config.ingameTickDelay).count();
            jConfig["StandbyTickDelay"] = std::chrono::duration_cast<std::chrono::milliseconds>(config.standbyTickDelay).count();
            jConfig["IsOverlayAllowed"] = config.isOverlayAllowed;

            std::ofstream configFile(path);
            configFile << std::setw(4) << jConfig << std::endl;

            WPRINT(std::format(L"Saved default confing in {}", path));
        }

        return config;
    }

    ConfigWrapper() noexcept
        : config(load_config())
    {}

public:
    // Singleton
    const static ConfigWrapper instance;

    // This contains the data
    const Config config;
};

// Link the static variable
const ConfigWrapper ConfigWrapper::instance;

// Create a shortcut to the current config instance
export const Config& config = ConfigWrapper::instance.config;
