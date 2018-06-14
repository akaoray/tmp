#pragma once

#include "base.h"

namespace xgine { namespace graphics { namespace core {

class Surface
{
public:
    static SPtr<Surface> Create(SPtr<Instance> instance, SPtr<Window> window);
    static void Destroy(Surface* surface);

    vk::SurfaceKHR GetNative();

private:
    Surface();
    ~Surface();

    vk::SurfaceKHR surface;

    SPtr<Instance> instance;
    SPtr<Window> window;

    DISALLOW_COPY_AND_ASSIGN(Surface);
};

} } }
