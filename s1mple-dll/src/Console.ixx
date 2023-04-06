module;

#include <thread>
#include <chrono>

export module Console;

export class Console 
{
public:
  Console() noexcept
  {
    if constexpr (isRelease) 
    {
      return;
    }

    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    SetConsoleTitleA("s1mple");

    // Open the console for stdout
    FILE* pStdout;
    freopen_s(&pStdout, "CON", "w", stdout);

    // Open the console for stderr
    FILE* pStderr;
    freopen_s(&pStderr, "CON", "w", stderr);

    puts("Console is ready!");
  }

  ~Console() noexcept
  {
    if constexpr (isRelease)
    {
      return;
    }

    if constexpr (isTesting)
    {
      exit_gracefully();
    }

    puts("Console is free!");
    FreeConsole();
  }

  void exit_gracefully() const noexcept
  {
    if constexpr (isRelease)
    {
      return;
    }

    constexpr int timeout = 5;
    for (int i = timeout; i > 0; i--)
    {
      std::cout << "Exiting in " << i << " seconds...\r";
      std::this_thread::sleep_for(std::chrono::seconds(1));
    } 
  }
};



