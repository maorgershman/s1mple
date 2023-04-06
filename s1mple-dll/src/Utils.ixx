module;

export module Utils;

export [[nodiscard]] bool is_mouse_cursor_hidden() noexcept
{
  CURSORINFO cursorInfo
  {
    .cbSize = sizeof(CURSORINFO),
  };

  if (GetCursorInfo(&cursorInfo))
  {
    return cursorInfo.flags == 0;
  }

  return false;
}