export module Keepalive;

import Keys;

export class Keepalive
{
    static constexpr auto subkey = "Software\\s1mple";
    static constexpr auto lastSeen = "LastSeen";
    static constexpr auto shouldDeload = "ShouldDeload";
    static constexpr auto delay = std::chrono::seconds(1);

    static constexpr auto terminationKey = Keys::Insert;

public:
    static void run()
    {
        while (!terminationKey.is_currently_pressed())
        {
            HKEY hKey;

            // Open registry in the desired location
            {
                const auto result = RegCreateKeyExA(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
                if (result != ERROR_SUCCESS)
                {
                    throw RuntimeError("Can't open main registry because RegCreateKeyExA has failed!");
                }
            }

            { // Update LastSeen
                const auto now = std::chrono::system_clock::now();
                const auto qwUnixTime = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

                // Set LastSeen to the current UNIX time.
                const auto result = RegSetValueExA(hKey, lastSeen, 0, REG_QWORD, (BYTE*)&qwUnixTime, sizeof(qwUnixTime));
                if (result != ERROR_SUCCESS)
                {
                    throw RuntimeError("Can't update LastSeen because RegSetValueExA has failed!");
                }
            }

            { // Check ShouldDeload
                DWORD dwShouldDeload = 0;

                // Read ShouldDeload from the registry.
                {
                    DWORD dwType = REG_DWORD;
                    DWORD dwCbData = sizeof(DWORD);

                    const auto result = RegQueryValueExA(hKey, shouldDeload, NULL, &dwType, (LPBYTE)&dwShouldDeload, &dwCbData);
                    if (result != ERROR_SUCCESS)
                    {
                        throw RuntimeError("Can't read ShouldDeload from the registry because RegQueryValueExA has failed!");
                    }
                }

                // If ShouldDeload is not 0:
                if (dwShouldDeload)
                {
                    // Set ShouldDeload to 0 and save.
                    dwShouldDeload = 0;
                    RegSetValueExA(hKey, shouldDeload, 0, REG_DWORD, (BYTE*)&dwShouldDeload, sizeof(REG_DWORD));
                    RegCloseKey(hKey);

                    // Exit the loop, this will make the dll deload.
                    break;
                }
            }

            // Close the registry key
            RegCloseKey(hKey);

            std::this_thread::sleep_for(delay);
        }
    }
};