find_package(Vulkan REQUIRED)

add_library(vkbootstrap STATIC)
add_library(glm INTERFACE)
add_library(vma INTERFACE)

add_library(stb_image INTERFACE)

add_library(tinyobjloader STATIC)

target_sources(vkbootstrap PRIVATE 
    vkbootstrap/VkBootstrap.h
    vkbootstrap/VkBootstrap.cpp
    vkbootstrap/VkBootstrapDispatch.h
    vkbootstrap/VkBootstrapFeatureChain.h
    vkbootstrap/VkBootstrapFeatureChain.inl
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

if(NOT SDL2_DIR)
    if(DEFINED ENV{SDL2_DIR})
        set(SDL2_DIR "$ENV{SDL2_DIR}" CACHE PATH "Path to SDL2Config.cmake")
    elseif(DEFINED ENV{VULKAN_SDK})
        set(SDL2_DIR "$ENV{VULKAN_SDK}/cmake" CACHE PATH "Path to SDL2Config.cmake")
    endif()
endif()
find_package(SDL2 CONFIG REQUIRED)
message(STATUS "SDL2 VERSION = ${SDL2_VERSION_MAJOR}.${SDL2_VERSION_MINOR}.${SDL2_VERSION_PATCH} in dir = ${SDL2_DIR}")
message(STATUS "SDL2_INCLUDE_DIRS = ${SDL2_INCLUDE_DIRS}, SDL2_LIBRARIES = ${SDL2_LIBRARIES}")

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
