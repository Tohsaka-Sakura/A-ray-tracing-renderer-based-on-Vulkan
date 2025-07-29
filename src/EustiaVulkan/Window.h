#pragma once

#include "WindowConfig.h"
#include "Vulkan.h"
#include <functional>
#include <vector>

namespace EustiaVulkan{
    
    class Window final
    {
    
    public:
        VULKAN_NON_COPIABLE(Window)

        explicit Window(const WinodwConfig& config);
        ~Window();

        const WinodwConfig& Config() const {return config_;}
        GLFWwindow* Handle()const {return window_;}
        float ContentScale() const;
        VkExtent2D FramebufferSize()const;
        VkExtent2D WindowSize() const;

        const char * GetKeyName(int key, int scancode) const;
        std::vector<const char*> GetRequiredInstanceExtensions()const;
        double GetTime() const;

        std::function<void()>DrawFrame;
        std::function<void(int key, int scancode, int action, int mods)> OnKey;
        std::function<void(double xpos, double ypos)> OnCursorPostion;
        std::function<void(int buttion, int action, int mods)> OnMouseButton;
        std::function<void(double xoffset, double yoffset)> OnScroll;
        
        void Close();
        bool IsMinimized() const;
        void Run();
        void WaitForEvents() const;

    private:
        const WinodwConfig config_;
        GLFWwindow* window_{};
    };
}