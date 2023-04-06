module;

export module Main;

import Console;
import Cheats;
import Keepalive;

export void run() noexcept
{
  Console console;
  std::thread(Keepalive::run).detach();

  try 
  {
    Cheats::init();
  }
  catch (...)
  {
    if constexpr (isDebug)
    {
      fputs("Main:run() failed!", stderr);
    }

    return;
  }

  Cheats::run();
}