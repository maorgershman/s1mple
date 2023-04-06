module;

export module Toggle;

import Keys;

export namespace Cheats
{
  export enum class ToggleMode
  {
    AlwaysOff,
    HoldKey,
    PressKey,
    AlwaysOn,
  };

  export struct ToggleInfo
  {
    const ToggleMode mode;
    const Key key;

    [[nodiscard]] bool is_toggled() const noexcept
    {
      switch (mode)
      {
      case ToggleMode::AlwaysOff:
        return false;
      case ToggleMode::AlwaysOn:
        return true;
      case ToggleMode::HoldKey:
        return key.is_currently_pressed();
      case ToggleMode::PressKey:
        return key.is_activated();
      }

      return false;
    }
  };
}