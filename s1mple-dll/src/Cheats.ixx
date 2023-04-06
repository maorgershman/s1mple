module;

export module Cheats;

import Keepalive;
import Offsets;
import Utils;

import BunnyHop;

export namespace Cheats
{
  export void init()
  {
    try
    {
      Offsets::load();
    }
    catch (const std::exception& ex)
    {
      if constexpr (isDebug)
      {
        fputs("Cheats::init() failed!", stderr);
      }

      throw ex;
    }
  }

  export void run() noexcept
  {
    while (Keepalive::is_alive())
    {
      BunnyHop::tick();

      if (!is_mouse_cursor_hidden())
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      else
      {
        if constexpr (isDebug)
        {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
      }
    }
  }
};
