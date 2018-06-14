#pragma once

#include "base.h"

#include "gpulist.h"

namespace xgine { namespace graphics { namespace core {

std::vector<const char*> GetRequiredDeviceExtensions();

class Device
{
public:
    struct Info
    {
        Gpu gpu;
        std::vector<const char*> requiredExtensions;

        Info(Gpu gpu_ = {}, std::vector<const char*> requiredExtensions_ = {})
            : gpu(gpu_), requiredExtensions(requiredExtensions_) {}
    };

    static SPtr<Device> Create(Info & info);
    static void Destroy(Device* device);

    Info GetInfo();
    vk::Device GetNative();
    vk::CommandPool GetCommandPool();
    vk::Queue GetGraphicsQueue();
    vk::Queue GetPresentQueue();

private:
    Device();
    ~Device();

    Info info;
    vk::Device device;

    vk::CommandPool commandPool;
    vk::Queue graphicsQueue;
    vk::Queue presentQueue;

    DISALLOW_COPY_AND_ASSIGN(Device);
};

} } }
