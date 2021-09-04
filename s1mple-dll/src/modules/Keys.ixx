export module Keys;

export enum class VirtualKey : int
{
    Mouse1 = VK_LBUTTON,
    Mouse2 = VK_RBUTTON,
    Mouse3 = VK_MBUTTON,
    Mouse4 = VK_XBUTTON2,
    Mouse5 = VK_XBUTTON1,
    Minus = VK_OEM_MINUS,
    Plus = VK_OEM_PLUS,
    Tilde = VK_OEM_3,
    Insert = VK_INSERT,
    Delete = VK_DELETE,
    Home = VK_HOME,
    End = VK_END,
    PageUp = VK_PRIOR,
    PageDown = VK_NEXT,
    F1 = VK_F1,
    F2 = VK_F2,
    F3 = VK_F3,
    F4 = VK_F4,
    F5 = VK_F5,
    F6 = VK_F6,
    F7 = VK_F7,
    F8 = VK_F8,
    F9 = VK_F9,
    F10 = VK_F10,
    F11 = VK_F11,
    F12 = VK_F12,
};

export struct Key
{
    const VirtualKey vKey;
    const std::string_view description;

    bool is_currently_pressed() const
    { 
        return GetAsyncKeyState(static_cast<int>(vKey)); 
    }

    Key operator=(const Key& key) 
    {
        return Key(key);
    }
};

namespace Keys
{
#define DEFINE_KEY(x) export constexpr Key x { .vKey = VirtualKey::x, .description = #x }

    DEFINE_KEY(Mouse1);
    DEFINE_KEY(Mouse2);
    DEFINE_KEY(Mouse3);
    DEFINE_KEY(Mouse4);
    DEFINE_KEY(Mouse5);

    DEFINE_KEY(Minus);
    DEFINE_KEY(Plus);
    DEFINE_KEY(Tilde);

    DEFINE_KEY(Insert);
    DEFINE_KEY(Delete);
    DEFINE_KEY(Home);
    DEFINE_KEY(End);
    DEFINE_KEY(PageUp);
    DEFINE_KEY(PageDown);

    DEFINE_KEY(F1);
    DEFINE_KEY(F2);
    DEFINE_KEY(F3);
    DEFINE_KEY(F4);
    DEFINE_KEY(F5);
    DEFINE_KEY(F6);
    DEFINE_KEY(F7);
    DEFINE_KEY(F8);
    DEFINE_KEY(F9);
    DEFINE_KEY(F10);
    DEFINE_KEY(F11);
    DEFINE_KEY(F12);

    export constexpr std::optional<Key> from_string(std::string_view str)
    {
#define CHECK_KEY(name) if (#name == str) return name

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