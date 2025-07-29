#pragma once

#include <cstdint>
#include <string>

namespace EustiaVulkan
{
    struct WinodwConfig final
    {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool CursorDisabled;
        bool Fullscreen;
        bool Resizeable;
    };
}