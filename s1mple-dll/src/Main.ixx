module;

export module Main;

import Console;
import Cheats;
import Keepalive;

export void run() noexcept
{
  Console console;

  try 
  {
    Cheats::init();
  }
  catch (const std::runtime_error& err)
  {
    if constexpr (isDebug)
    {
      std::cerr << "Cheats::init() failed:" << std::endl;
      std::cerr << err.what() << std::endl;
    }

    return;
  }

  Keepalive keepalive;
  keepalive.run();
}