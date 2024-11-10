#pragma once

#include <cstdint>

namespace gui
{
namespace common
{
enum WindowInputBit : uint16_t
{
    MOUSE_CLICK = 1 << 0,
    MOUSE_MOVE   = 1 << 1,
};
} // namespace common
} // namespace gui