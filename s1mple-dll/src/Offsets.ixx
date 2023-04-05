module;

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <unordered_map>
#include <string>

export module Offsets;

export class Offsets
{
	static uint64_t timestamp;
	static std::unordered_map<std::string_view, ptrdiff_t>
		signatures,
		netvars;

public:
	static void load()
	{
		constexpr auto url = "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json";

		auto fetchResponse = cpr::Get(cpr::Url{ url });
		if (fetchResponse.error) 
		{
			throw std::runtime_error(fetchResponse.error.message);
		}

		auto json = nlohmann::json::parse(fetchResponse.text);

		timestamp = json["timestamp"].get<uint64_t>();
		for (auto& [key, val] : json["signatures"].items())
		{
			signatures[key] = val;
		}

		for (auto& [key, val] : json["netvars"].items())
		{
			netvars[key] = val;
		}

		if constexpr (isDebug)
		{
			std::cout << "timestamp: " << timestamp << std::endl;
			std::cout << "signatures:" << std::endl;
			for (const auto& [key, value] : signatures)
			{
				std::cout << "  " << key << ": " << value << std::endl;
			}

			std::cout << "netvars:" << std::endl;
			for (const auto& [key, value] : netvars)
			{
				std::cout << "  " << key << ": " << value << std::endl;
			}
		}
	}
};

uint64_t Offsets::timestamp;
std::unordered_map<std::string_view, ptrdiff_t>
	Offsets::signatures,
	Offsets::netvars;
