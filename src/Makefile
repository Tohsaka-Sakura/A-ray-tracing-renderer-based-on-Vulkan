VULKAN_INCLUDE_PATH = /usr/include/vulkan
STB_INCLUDE_PATH = /home/eustia/E/code/c++/cppsoft/stb/

CXXFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

CXXFLAGS += -I$(VULKAN_INCLUDE_PATH) -I$(STB_INCLUDE_PATH)

VulkanTest: main.cpp
	g++ $(CXXFLAGS) -o VulkanTest main.cpp $(LDFLAGS)

.PHONY: test clean

VulkanTestOri: main_ba1.cpp
	g++ $(CXXFLAGS) -o VulkanTestOri main_ba1.cpp $(LDFLAGS)

test: VulkanTest
	./VulkanTest

test_ori: VulkanTestOri
	./VulkanTestOri

all: VulkanTest VulkanTestOri

clean:
	rm -f VulkanTest
	rm -f VulkanTestOri