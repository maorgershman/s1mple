#pragma once

#include <Windows.h>
#include <shlobj.h>

#include <string>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
#include <fstream>
#include <source_location>

#ifdef _DEBUG

#include <iostream>

#define PRINT(x)\
    std::cout << x << std::endl

#else

#define PRINT(x)

#endif // _DEBUG

class RuntimeError : public std::runtime_error
{
    std::string log(const std::string_view message, const std::source_location l)
    {
        std::stringstream ss;
        ss << l.file_name() << "(" << l.line() << ":" << l.column() << ") `" << l.function_name() << "`: " << message << '\n';
        return ss.str();
    }

public:
    RuntimeError(const std::string_view message) :
        runtime_error(log(message, std::source_location::current()))
    {}
};
