module;

export module Cheats;

import Offsets;

export class Cheats 
{
public:
  static void init()
  {
    try
    {
      Offsets::load();
    }
    catch (const std::runtime_error& err)
    {
      if constexpr (isDebug)
      {
        std::cerr << "Offsets::init() failed:" << std::endl;
        std::cerr << err.what() << std::endl;
      }

      throw err;
    }
  }
};