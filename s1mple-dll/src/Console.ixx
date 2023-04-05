module;

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

    std::cout << "Console is ready!" << std::endl;
	}

	~Console() noexcept
	{
    if constexpr (isRelease)
    {
      return;
    }

    std::cout << "Console is free!" << std::endl;
    FreeConsole();
	}
};



