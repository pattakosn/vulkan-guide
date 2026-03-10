#pragma once

#include "vk_types.h"
#include <string>

namespace vkutil
{
bool load_shader_module(const char* filePath,
    VkDevice device,
    VkShaderModule* outShaderModule);

// Searches for a file by name recursively: first in all subdirs of the
// executable directory, then one level up and again in all subdirs.
// Returns the full path if found, or an empty string otherwise.
std::string find_shader(const char* fileName);
}
