#pragma once

#define NOMINMAX
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#undef APIENTPY

#define VULKAN_NON_COPIABLE(className)\
    className(const className&) = delete; \
    className(className&&) = delete;\
    className& operator = (const className&) = delete;\
    className& operator = (className&&) = delete;

#define VULKAN_HANDLE(Type, name)\
public:\
    Type Handle() const {return name;}\
private:\
    Type name{};

namespace EustiaVulkan
{
    void check(VkResult result, const char * operation);
    const char* ToString(VkResult result);
}