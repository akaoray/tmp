#pragma once

#include "base.h"

namespace xgine { namespace graphics { namespace core {

class RenderPass
{
public:
    struct Info
    {
        vk::Format format;

        Info(vk::Format format_ = vk::Format::eUndefined) :
            format(format_) {}
    };

    static SPtr<RenderPass> Create(SPtr<Device> device, Info & info);
    static void Destroy(RenderPass* renderPass);

    Info GetInfo();
    vk::RenderPass GetNative();

private:
    RenderPass();
    ~RenderPass();

    Info info;
    vk::RenderPass renderPass;

    SPtr<Device> device;

    DISALLOW_COPY_AND_ASSIGN(RenderPass);
};

} } }

