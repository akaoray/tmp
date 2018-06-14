#pragma once

#include "base.h"

namespace xgine { namespace graphics { namespace core {

class SwapChain
{
public:
    struct Info
    {
        uint32_t width;
        uint32_t height;
        bool vsync;

        Info(uint32_t width_ = 800, uint32_t height_ = 600, bool vsync_ = true)
            : width(width_), height(height_), vsync(vsync_) {}
    };

    static SPtr<SwapChain> Create(SPtr<Surface> surface, SPtr<Device> device, Info & info);
    static void Destroy(SwapChain* swapChain);

    Info GetInfo();
    vk::Format GetFormat();
    vk::SwapchainKHR GetNative();
    std::vector<vk::ImageView> GetImageViews();

private:
    SwapChain();
    ~SwapChain();

    Info info;
    vk::Format format;
    vk::SwapchainKHR swapChain;
    std::vector<vk::Image> images;
    std::vector<vk::ImageView> imageViews;

    SPtr<Device> device;

    DISALLOW_COPY_AND_ASSIGN(SwapChain);
};

} } }
