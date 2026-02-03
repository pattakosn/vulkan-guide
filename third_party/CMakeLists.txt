find_package(Vulkan REQUIRED)

add_library(vkbootstrap STATIC)
add_library(glm INTERFACE)
add_library(vma INTERFACE)

add_library(stb_image INTERFACE)

add_library(tinyobjloader STATIC)

target_sources(vkbootstrap PRIVATE 
    vkbootstrap/VkBootstrap.h
    vkbootstrap/VkBootstrap.cpp
    )

target_include_directories(vkbootstrap PUBLIC vkbootstrap)
target_link_libraries(vkbootstrap PUBLIC Vulkan::Vulkan $<$<BOOL:UNIX>:${CMAKE_DL_LIBS}>)

#both vma and glm and header only libs so we only need the include path
target_include_directories(vma INTERFACE vma)
target_include_directories(glm INTERFACE glm)

target_sources(tinyobjloader PRIVATE 
    tinyobjloader/tiny_obj_loader.h
    tinyobjloader/tiny_obj_loader.cc
    )

target_include_directories(tinyobjloader PUBLIC tinyobjloader)

set(SDL2_DIR "C:/VulkanSDK/1.4.335.0/cmake" CACHE PATH "Path to SDL2Config.cmake")
#or list(APPEND CMAKE_PREFIX_PATH "C:/VulkanSDK/1.4.335.0")
find_package(SDL2 CONFIG REQUIRED)
message(STATUS "SDL2_FOUND = ${SDL2_FOUND} , SDL2_VERSION = ${SDL2_VERSION}, SDL2_DIR = ${SDL2_DIR}")

add_library(imgui STATIC)

target_include_directories(imgui PUBLIC imgui)

target_sources(imgui PRIVATE 
    imgui/imgui.h
    imgui/imgui.cpp

    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp

    imgui/imgui_impl_vulkan.cpp
    imgui/imgui_impl_sdl.cpp
    )

target_link_libraries(imgui PUBLIC Vulkan::Vulkan SDL2::SDL2 SDL2::SDL2main)# sdl2)
#target_compile_definitions(imgui PUBLIC SDL_MAIN_HANDLED)

target_include_directories(stb_image INTERFACE stb_image)
