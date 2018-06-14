/*#include "context.h"

#include "instance.h"
#include "window.h"

namespace xgine {

namespace graphics {

std::vector<const char*> GetRequiredDeviceExtensions()
{
    XDEBUG();

    return {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
}

Context::Context()
{
    XDEBUG();
}

Context::~Context()
{
    XDEBUG();
}

std::shared_ptr<Context> Context::Create(std::shared_ptr<Instance> & instance, std::shared_ptr<Window> & window, Info & info)
{
    XDEBUG();

    std::shared_ptr<Context> context(new Context(), Context::Destroy);
    context->instance = instance;
    context->info = info;

    // Create surface
    VkSurfaceKHR surface = nullptr;
    if(glfwCreateWindowSurface(instance->GetNative(), window->GetNative(), nullptr, &surface) != VK_SUCCESS)
    {
        XMESSAGE("Invalid glfwCreateWindowSurface");
        return nullptr;
    }
    context->surface = surface;

    // Get physical devices
    std::vector<vk::PhysicalDevice> physicalDevices;
    if(info.physicalDevice) physicalDevices.push_back(info.physicalDevice);
    else physicalDevices = instance->GetNative().enumeratePhysicalDevices();

    if(physicalDevices.empty())
    {
        XMESSAGE("Invalid enumeratePhysicalDevices");
        return nullptr;
    }

    // Get gpus info and pick gpu
    for(auto & physicalDevice : physicalDevices)
    {
        Gpu gpu = {};
        gpu.physicalDevice = physicalDevice;
        gpu.queueFamilyProperties = gpu.physicalDevice.getQueueFamilyProperties();

        // Get graphicsQueueFamilyIndex
        gpu.graphicsQueueFamilyIndex = std::distance(gpu.queueFamilyProperties.begin(),
                                                     std::find_if(gpu.queueFamilyProperties.begin(),
                                                                  gpu.queueFamilyProperties.end(),
                                                                  [](vk::QueueFamilyProperties const& qfp) { return qfp.queueFlags & vk::QueueFlagBits::eGraphics; }));

        // Get presentQueueFamilyIndex
        gpu.presentQueueFamilyIndex = gpu.physicalDevice.getSurfaceSupportKHR(static_cast<uint32_t>(gpu.graphicsQueueFamilyIndex), context->surface) ? gpu.graphicsQueueFamilyIndex : gpu.queueFamilyProperties.size();
        if (gpu.presentQueueFamilyIndex == gpu.queueFamilyProperties.size())
        {
            // the graphicsQueueFamilyIndex doesn't support present -> look for an other family index that supports both graphics and present
            for (size_t i = 0; i < gpu.queueFamilyProperties.size(); i++)
            {
                if ((gpu.queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) && gpu.physicalDevice.getSurfaceSupportKHR(static_cast<uint32_t>(i), context->surface))
                {
                    gpu.graphicsQueueFamilyIndex = i;
                    gpu.presentQueueFamilyIndex = i;
                    break;
                }
            }
            if (gpu.presentQueueFamilyIndex == gpu.queueFamilyProperties.size())
            {
                // there's nothing like a single family index that supports both graphics and present -> look for an other family index that supports present
                for (size_t i = 0; i < gpu.queueFamilyProperties.size(); i++)
                {
                    if (gpu.physicalDevice.getSurfaceSupportKHR(static_cast<uint32_t>(i), context->surface))
                    {
                        gpu.presentQueueFamilyIndex = i;
                        break;
                    }
                }
            }
        }
        if ((gpu.graphicsQueueFamilyIndex == gpu.queueFamilyProperties.size()) || (gpu.presentQueueFamilyIndex == gpu.queueFamilyProperties.size()))
        {
            // Ignore not supported device
            continue;
        }

        gpu.physicalDeviceProperties = gpu.physicalDevice.getProperties();
        gpu.physicalDeviceFeatures = gpu.physicalDevice.getFeatures();
        gpu.physicalDeviceMemoryProperties = gpu.physicalDevice.getMemoryProperties();

        if((gpu.physicalDeviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) && !context->pickGpu.physicalDevice)
        {
            context->pickGpu = gpu;
        }

        context->gpus.push_back(gpu);
    }

    if(context->gpus.empty())
    {
        XMESSAGE("Invalid find gpus");
        return nullptr;
    }

    if(!context->pickGpu.physicalDevice)
    {
        XMESSAGE("Invalid pick eDiscreteGpu, will be picked first valid");
        context->pickGpu = context->gpus[0];
    }

    // Create physical device
    float queuePriority = 0.0f;
    vk::DeviceQueueCreateInfo deviceQueueCreateInfo({}, static_cast<uint32_t>(context->pickGpu.graphicsQueueFamilyIndex), 1, &queuePriority);
    context->device = context->pickGpu.physicalDevice.createDevice(vk::DeviceCreateInfo({}, 1, &deviceQueueCreateInfo, 0, nullptr, static_cast<uint32_t>(info.requiredDeviceExtensions.size()), info.requiredDeviceExtensions.data()));

    if(!context->device)
    {
        XMESSAGE("Invalid createDevice");
        return nullptr;
    }

    vk::CommandPoolCreateInfo commandPoolCreateInfo;
    commandPoolCreateInfo.queueFamilyIndex = context->pickGpu.graphicsQueueFamilyIndex;
    commandPoolCreateInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
    context->commandPool = context->device.createCommandPool(commandPoolCreateInfo);

    context->graphicsQueue = context->device.getQueue(context->pickGpu.graphicsQueueFamilyIndex, 0);
    context->presentQueue = context->device.getQueue(context->pickGpu.presentQueueFamilyIndex, 0);

    return context;
}

void Context::Destroy(Context* context)
{
    XDEBUG();

    assert(context != nullptr);

    if(context->commandPool) context->device.destroyCommandPool(context->commandPool);
    if(context->device) context->device.destroy();
    if(context->surface) context->instance->GetNative().destroySurfaceKHR(context->surface);

    delete context;
}

Context::Info Context::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::SurfaceKHR Context::GetSurface()
{
    XDEBUG();

    return this->surface;
}


std::vector<Gpu> Context::GetGpus()
{
    XDEBUG();

    return this->gpus;
}

Gpu Context::GetPickGpu()
{
    XDEBUG();

    return this->pickGpu;
}

vk::Device Context::GetDevice()
{
    //XDEBUG();

    return this->device;
}

vk::CommandPool Context::GetCommandPool()
{
    XDEBUG();

    return this->commandPool;
}

vk::Queue Context::GetGraphicsQueue()
{
    XDEBUG();

    return this->graphicsQueue;
}

vk::Queue Context::GetPresentQueue()
{
    XDEBUG();

    return this->presentQueue;
}

vk::Bool32 Context::getMemoryType(uint32_t typeBits, const vk::MemoryPropertyFlags& properties, uint32_t* typeIndex) const {
    for (uint32_t i = 0; i < 32; i++) {
        if ((typeBits & 1) == 1) {
            if ((this->pickGpu.physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                *typeIndex = i;
                return VK_TRUE;
            }
        }
        typeBits >>= 1;
    }
    return VK_FALSE;
}

uint32_t Context::getMemoryType(uint32_t typeBits, const vk::MemoryPropertyFlags& properties) const {
    uint32_t result = 0;
    if (VK_FALSE == getMemoryType(typeBits, properties, &result)) {
        XMESSAGE("Unable to find memory type " + vk::to_string(properties));
    }
    return result;
}

}

}

*/
