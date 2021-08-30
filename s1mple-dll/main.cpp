import Keepalive;

void run()
{
    Keepalive::run();
}

#ifdef _DEBUG

int main()
{
    run();
}

#else

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        std::thread(run).detach();
    }
    return TRUE;
}

#endif // _DEBUG