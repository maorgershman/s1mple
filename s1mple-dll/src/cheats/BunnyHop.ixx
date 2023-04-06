module;

export module BunnyHop;

import Offsets;
import Toggle;
import Utils;

export namespace Cheats
{
	export struct BunnyHop
	{
		static constexpr ToggleInfo toggleInfo
		{
			.mode = ToggleMode::AlwaysOn,
		};

		static void tick() noexcept
		{
			if (!toggleInfo.is_toggled())
			{
				return;
			}

			if (!is_mouse_cursor_hidden())
			{
				return;
			}

			const auto& o = Offsets::values;
			const auto localPlayer = read_memory<uint32_t>(o.client + o.signatures.at("dwLocalPlayer"));
			const auto localPlayerFlags = read_memory<uint8_t>(localPlayer + o.netvars.at("m_fFlags"));

			const bool isSpacedPressed = Keys::Space.is_currently_pressed();
			const bool isOnGround = localPlayerFlags & (1 << 0);

			if (isSpacedPressed && isOnGround)
			{
				write_memory<uint32_t>(o.client + o.signatures.at("dwForceJump"), 6);
			}
		}
	};
}