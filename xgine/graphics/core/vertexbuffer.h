#pragma once

#include "base.h"

#include "buffer.h"

namespace xgine { namespace graphics { namespace core {

class VertexBuffer
{
public:
    enum class LayoutType
    {
        POSITION,
        COLOR,
        NORMAL,
        TEXCOORD
    };

    struct Layout
    {
        LayoutType layoutType;
        uint32_t size;
    };

    struct Info
    {
        uint32_t size;
        uint32_t stride;
        std::vector<Layout> layouts;

        Info(uint32_t size_ = 0, uint32_t stride_ = 0, std::vector<Layout> layouts_ = {})
            : size(size_), stride(stride_), layouts(layouts_) {}
    };

    static SPtr<VertexBuffer> Create(SPtr<Device> device, void* data, Info & info);
    static void Destroy(VertexBuffer* vertexBuffer);

    Info GetInfo();
    vk::Buffer GetNative();
    SPtr<Buffer> GetBuffer();

private:
    VertexBuffer();
    ~VertexBuffer();

    Info info;
    SPtr<Buffer> buffer;

    SPtr<Device> device;

    DISALLOW_COPY_AND_ASSIGN(VertexBuffer);
};

} } }
