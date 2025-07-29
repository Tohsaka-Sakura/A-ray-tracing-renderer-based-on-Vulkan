cmake_minimum_required(VERSION 3.10)
project(VulkanTestProject LANGUAGES CXX)

# --- 定义包含路径 ---
set(VULKAN_INCLUDE_PATH "/usr/include/vulkan")
set(STB_INCLUDE_PATH "/home/eustia/E/code/c++/cppsoft/stb/")
set(TINYOBJ_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/thirdParties/tinyobjloader")

# --- 设置源文件和资源文件根目录 ---
set(SOURCE_AND_RESOURCE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SHADERS_SOURCE_DIR "${SOURCE_AND_RESOURCE_ROOT_DIR}/shaders") # 着色器源文件目录
set(SHADERS_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")      # 编译后 SPIR-V 文件的目标目录

# --- 查找 glslc 编译器 ---
find_program(GLSLC_COMPILER glslc HINTS "$ENV{VULKAN_SDK}/bin" /usr/local/bin /usr/bin)

if(NOT GLSLC_COMPILER)
    message(FATAL_ERROR "glslc compiler not found! Please ensure Vulkan SDK is installed and GLSLC_COMPILER is in your PATH or VULKAN_SDK environment variable is set.")
endif()

# --- 自动编译着色器 ---
# 确保目标目录存在
file(MAKE_DIRECTORY ${SHADERS_BUILD_DIR})

# 获取所有着色器文件（.vert, .frag, .comp 等）
file(GLOB_RECURSE GLSL_SHADERS "${SHADERS_SOURCE_DIR}/*.vert"
                               "${SHADERS_SOURCE_DIR}/*.frag"
                               "${SHADERS_SOURCE_DIR}/*.comp"
                               "${SHADERS_SOURCE_DIR}/*.geom"
                               "${SHADERS_SOURCE_DIR}/*.tesc"
                               "${SHADERS_SOURCE_DIR}/*.tese")

# 为每个着色器文件添加自定义编译命令
set(SPIRV_SHADERS "") # 用于收集所有编译后的 SPIR-V 文件
foreach(GLSL_SHADER ${GLSL_SHADERS})
    # 获取文件名（不带路径和扩展名）
    get_filename_component(SHADER_NAME "${GLSL_SHADER}" NAME_WE)
    # get_filename_component(ORIGINAL_EXT "${GLSL_SHADER}" EXT) # 不再需要原始扩展名

    # --- 关键修改处 ---
    # 构造 SPIR-V 文件名：直接使用文件名（不带原始扩展名）并追加 .spv
    set(SPIRV_OUTPUT_FILE "${SHADERS_BUILD_DIR}/${SHADER_NAME}.spv")

    # 添加自定义命令来编译着色器
    add_custom_command(
        OUTPUT  ${SPIRV_OUTPUT_FILE}
        COMMAND ${GLSLC_COMPILER} -o ${SPIRV_OUTPUT_FILE} ${GLSL_SHADER}
        DEPENDS ${GLSL_SHADER}
        COMMENT "Compiling shader: ${GLSL_SHADER} -> ${SPIRV_OUTPUT_FILE}"
    )
    # 将编译后的 SPIR-V 文件添加到列表中
    list(APPEND SPIRV_SHADERS ${SPIRV_OUTPUT_FILE})
endforeach()

# --- 复制其他运行时资源文件 (如果存在) ---
file(COPY "${SOURCE_AND_RESOURCE_ROOT_DIR}/textures/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/textures")
file(COPY "${SOURCE_AND_RESOURCE_ROOT_DIR}/models/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/models")
file(COPY "${SOURCE_AND_RESOURCE_ROOT_DIR}/materials/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/materials")


# --- 全局编译选项 ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

# 全局添加包含目录
include_directories(
    ${VULKAN_INCLUDE_PATH}
    ${STB_INCLUDE_PATH}
    ${TINYOBJ_INCLUDE_PATH}
)

# --- 链接库 ---
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

set(COMMON_LIBS
    Vulkan::Vulkan
    glfw
    dl
    pthread
    X11
    Xxf86vm
    Xrandr
    Xi
)

# --- 构建目标 ---
add_executable(VulkanTest ${SOURCE_AND_RESOURCE_ROOT_DIR}/main.cpp ${SPIRV_SHADERS})
target_link_libraries(VulkanTest PRIVATE ${COMMON_LIBS})

add_executable(VulkanTestOri ${SOURCE_AND_RESOURCE_ROOT_DIR}/main_ba1.cpp ${SPIRV_SHADERS})
target_link_libraries(VulkanTestOri PRIVATE ${COMMON_LIBS})

# --- 自定义目标 ---
add_custom_target(test ALL COMMAND $<TARGET_FILE:VulkanTest>)
# add_custom_target(test_ori ALL COMMAND $<TARGET_FILE:VulkanTestOri>)
# add_custom_target(all ALL DEPENDS VulkanTest VulkanTestOri)