#pragma once

#include "base.h"

#include "buffer.h"

namespace xgine { namespace graphics { namespace core {

class UniformBuffer
{
public:
    struct Info
    {
        uint32_t size;

        Info(uint32_t size_ = 0)
            : size(size_) {}
    };

    static SPtr<UniformBuffer> Create(SPtr<Device> device, void* data, Info & info);
    static void Destroy(UniformBuffer* indexBuffer);

    Info GetInfo();
    vk::Buffer GetNative();
    SPtr<Buffer> GetBuffer();

    bool Update(void* data, uint32_t offset, uint32_t size);

private:
    UniformBuffer();
    ~UniformBuffer();

    Info info;
    SPtr<Buffer> buffer;

    SPtr<Device> device;

    DISALLOW_COPY_AND_ASSIGN(UniformBuffer);
};

} } }
