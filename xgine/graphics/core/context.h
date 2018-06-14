/*#pragma once

#include "base.h"

#include "gpu.h"

namespace xgine { namespace graphics { namespace core {

std::vector<const char*> GetRequiredDeviceExtensions();

class Context
{
public:
    struct Info
    {
        vk::PhysicalDevice physicalDevice;
        std::vector<const char*> requiredDeviceExtensions;

        Info(vk::PhysicalDevice physicalDevice_ = vk::PhysicalDevice(), std::vector<const char*> requiredDeviceExtensions_ = GetRequiredDeviceExtensions())
            : physicalDevice(physicalDevice_), requiredDeviceExtensions(requiredDeviceExtensions_) {}
    };

    static std::shared_ptr<Context> Create(std::shared_ptr<Instance> & instance, std::shared_ptr<Window> & window, Info & info);
    static void Destroy(Context* context);

    Info GetInfo();
    vk::SurfaceKHR GetSurface();
    std::vector<Gpu> GetGpus();
    Gpu GetPickGpu();
    vk::Device GetDevice();
    vk::CommandPool GetCommandPool();
    vk::Queue GetGraphicsQueue();
    vk::Queue GetPresentQueue();

    vk::Bool32 getMemoryType(uint32_t typeBits, const vk::MemoryPropertyFlags& properties, uint32_t* typeIndex) const;
    uint32_t getMemoryType(uint32_t typeBits, const vk::MemoryPropertyFlags& properties) const;

private:
    Context();
    ~Context();

    Info info;
    vk::SurfaceKHR surface;
    std::vector<Gpu> gpus;
    Gpu pickGpu;
    vk::Device device;
    vk::CommandPool commandPool;
    vk::Queue graphicsQueue;
    vk::Queue presentQueue;

    std::shared_ptr<Instance> instance;

    DISALLOW_COPY_AND_ASSIGN(Context);
};

} } }*/
