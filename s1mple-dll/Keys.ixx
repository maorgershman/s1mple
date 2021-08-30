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
#define DEFINE_KEY(name, vk)\
    export constexpr Key name { .vKey = vk, .description = #name }
#define DEFINE_KEY_SHORT(name)\
    DEFINE_KEY(name, VK_##name)

    export constexpr Key Null{ .vKey = 0, .description = std::string_view() };

    DEFINE_KEY(Mouse1, VK_LBUTTON);
    DEFINE_KEY(Mouse2, VK_RBUTTON);
    DEFINE_KEY(Mouse3, VK_MBUTTON);
    DEFINE_KEY(Mouse4, VK_XBUTTON2);
    DEFINE_KEY(Mouse5, VK_XBUTTON1);

    DEFINE_KEY(Minus, VK_OEM_MINUS);
    DEFINE_KEY(Plus, VK_OEM_PLUS);
    DEFINE_KEY(Tilde, VK_OEM_3);

    DEFINE_KEY(Insert, VK_INSERT);
    DEFINE_KEY(Delete, VK_DELETE);
    DEFINE_KEY(Home, VK_HOME);
    DEFINE_KEY(End, VK_END);
    DEFINE_KEY(PageUp, VK_PRIOR);
    DEFINE_KEY(PageDown, VK_NEXT);

    DEFINE_KEY_SHORT(F1);
    DEFINE_KEY_SHORT(F2);
    DEFINE_KEY_SHORT(F3);
    DEFINE_KEY_SHORT(F4);
    DEFINE_KEY_SHORT(F5);
    DEFINE_KEY_SHORT(F6);
    DEFINE_KEY_SHORT(F7);
    DEFINE_KEY_SHORT(F8);
    DEFINE_KEY_SHORT(F9);
    DEFINE_KEY_SHORT(F10);
    DEFINE_KEY_SHORT(F11);
    DEFINE_KEY_SHORT(F12);

    export std::optional<Key> from_string(const std::string& str)
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
        return F12;
    }
}