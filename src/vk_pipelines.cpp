#include "vk_pipelines.h"
#include <fstream>
#include <filesystem>
#include <iostream>

bool vkutil::load_shader_module(const char* filePath,
    VkDevice device,
    VkShaderModule* outShaderModule)
{
    // open the file. With cursor at the end
    std::ifstream file(filePath, std::ios::ate | std::ios::binary);

    if (!file.is_open())
        return false;

    // find what the size of the file is by looking up the location of the cursor
    // because the cursor is at the end, it gives the size directly in bytes
    size_t fileSize = (size_t)file.tellg();

    // spirv expects the buffer to be on uint32, so make sure to reserve a int
    // vector big enough for the entire file
    std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));

    // put file cursor at beginning
    file.seekg(0);

    // load the entire file into the buffer
    file.read((char*)buffer.data(), fileSize);

    // now that the file is loaded into the buffer, we can close it
    file.close();

    // create a new shader module, using the buffer we loaded
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pNext = nullptr;

    // codeSize has to be in bytes, so multply the ints in the buffer by size of
    // int to know the real size of the buffer
    createInfo.codeSize = buffer.size() * sizeof(uint32_t);
    createInfo.pCode = buffer.data();

    // check that the creation goes well.
    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
        return false;
    *outShaderModule = shaderModule;
    return true;
}

std::string vkutil::find_shader(const char* fileName)
{
    namespace fs = std::filesystem;

    fs::path skipDir;

    auto searchRecursive = [&](const fs::path& root) -> std::string {
        for (auto it = fs::recursive_directory_iterator(root, fs::directory_options::skip_permission_denied);
             it != fs::recursive_directory_iterator(); ++it) {
            if (it->is_directory() && !skipDir.empty() && fs::equivalent(it->path(), skipDir)) {
                it.disable_recursion_pending();
                continue;
            }
            if (it->is_regular_file() && it->path().filename() == fileName)
                return it->path().string();
        }
        return {};
    };

    try {
        // Start from the current directory, keep going up until root
        fs::path dir = fs::current_path();

        while (true) {
            std::string result = searchRecursive(dir);
            if (!result.empty()) {
                std::cout << "Found shader: " << result << "\n";
                return result;
            }

            skipDir = dir;
            fs::path parent = dir.parent_path();
            if (parent == dir) break;
            dir = parent;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error while searching for shader \"" << fileName << "\n";
        std::exit(1);
    }

    std::cerr << "Could not find shader file: " << fileName << "\n";
    return {};
}
