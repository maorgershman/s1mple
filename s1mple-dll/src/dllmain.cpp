#ifndef TESTING

#include <thread>

import Main;

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
  if (fdwReason == DLL_PROCESS_ATTACH)
  {
    std::thread(run).detach();
  }

  return TRUE;
}

#endif