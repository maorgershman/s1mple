#ifdef TESTING

#include <thread>

import Main;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  std::thread(run).join();

  return 0;
}

#endif