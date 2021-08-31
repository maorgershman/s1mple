export module Keys;

export struct Key
{
    const int vKey;
    const std::string_view description;

    bool is_currently_pressed() const
    { 
        return GetAsyncKeyState(vKey); 
    }
};

namespace Keys
{
    // Since VS2022 C++20 IntelliSense is broken, don't define this using macros!

    export 
        extern // 'extern' is redundant here according to cppreference (and the compiler), but IntelliSense says otherwise.
        constexpr Key 
        Mouse1{ .vKey = VK_LBUTTON, .description = "Mouse1" },
        Mouse2{ .vKey = VK_RBUTTON, .description = "Mouse2" },
        Mouse3{ .vKey = VK_MBUTTON, .description = "Mouse3" },
        Mouse4{ .vKey = VK_XBUTTON2, .description = "Mouse4" },
        Mouse5{ .vKey = VK_XBUTTON1, .description = "Mouse5" },
        
        Minus{ .vKey = VK_OEM_MINUS, .description = "Minus" },
        Plus{ .vKey = VK_OEM_PLUS, .description = "Plus" },
        Tilde{ .vKey = VK_OEM_3, .description = "Tilde" },
        
        Insert{ .vKey = VK_INSERT, .description = "Insert" },
        Delete{ .vKey = VK_DELETE, .description = "Delete" },
        Home{ .vKey = VK_HOME, .description = "Home" },
        End{ .vKey = VK_END, .description = "End" },
        PageUp{ .vKey = VK_PRIOR, .description = "PageUp" },
        PageDown{ .vKey = VK_NEXT, .description = "PageDown" },
        
        F1{ .vKey = VK_F1, .description = "F1" },
        F2{ .vKey = VK_F2, .description = "F2" },
        F3{ .vKey = VK_F3, .description = "F3" },
        F4{ .vKey = VK_F4, .description = "F4" },
        F5{ .vKey = VK_F5, .description = "F5" },
        F6{ .vKey = VK_F6, .description = "F6" },
        F7{ .vKey = VK_F7, .description = "F7" },
        F8{ .vKey = VK_F8, .description = "F8" },
        F9{ .vKey = VK_F9, .description = "F9" },
        F10{ .vKey = VK_F10, .description = "F10" },
        F11{ .vKey = VK_F11, .description = "F11" },
        F12{ .vKey = VK_F12, .description = "F12" };
    
    export constexpr std::optional<Key> from_string(std::string_view str)
    {
#define CHECK_KEY(name)\
        if (#name == str)\
            return name

        CHECK_KEY(Mouse1);
        CHECK_KEY(Mouse2);
        CHECK_KEY(Mouse3);
        CHECK_KEY(Mouse4);
        CHECK_KEY(Mouse5);
        CHECK_KEY(Minus);
        CHECK_KEY(Plus);
        CHECK_KEY(Tilde);
        CHECK_KEY(Insert);
        CHECK_KEY(Delete);
        CHECK_KEY(Home);
        CHECK_KEY(End);
        CHECK_KEY(PageUp);
        CHECK_KEY(PageDown);
        CHECK_KEY(F1);
        CHECK_KEY(F2);
        CHECK_KEY(F3);
        CHECK_KEY(F4);
        CHECK_KEY(F5);
        CHECK_KEY(F6);
        CHECK_KEY(F7);
        CHECK_KEY(F8);
        CHECK_KEY(F9);
        CHECK_KEY(F10);
        CHECK_KEY(F11);
        CHECK_KEY(F12);

        return {};
    }
}