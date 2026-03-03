VkBootstrap lib -> vulkan setup helper library
Bolk lib -> vulkan function + extension loader library

VkInstance 
VkPhysicalDevice
VkDevice
Swapchain 
  NOT needed for offline rendering or compute
  recreate if image size changes
  2-3 images or image-views are enough for double or triple buffering
  PresentMode

VkImage: a handle to actual image object to use as texture or to render into
VkImageView: a wrapper for that image

VkCommandPool 
  -> VkCommandBuffer: Start in Ready state, vkBeginCommandBuffer -> Recording state -> vkEndCommandBuffer finish recording commands and put it in Executable state
    -> VkCmdXXXXX to record commands in VkCommandBuffer
      -> VkQueue submision. several VkQueueFamilies
        -> vkQueueSubmit  submitted cmd buffer is put in the Pending state
          -> vkResetCommandBuffer not safe unles the gpu has finished executing cmd buffer
