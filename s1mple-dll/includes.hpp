#pragma once

#include <Windows.h>
#include <shlobj.h>

#include <string>
#include <string_view>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <source_location>
#include <format>

#ifdef _DEBUG

#include <iostream>

#define PRINT(x)\
    std::cout << x << std::endl

#define WPRINT(x)\
    std::wcout << x << std::endl

#else

#define PRINT(x)

#endif // _DEBUG

class RuntimeError : public std::runtime_error
{
    std::string log(std::string_view message, const std::source_location l)
    {
        std::stringstream ss;
        ss << l.file_name() << "(" << l.line() << ":" << l.column() << ") `" << l.function_name() << "`: " << message << '\n';
        return ss.str();
    }

public:
    RuntimeError(std::string_view message) :
        runtime_error(log(message, std::source_location::current()))
    {}
};
