#pragma once

#include "base.h"

#include "buffer.h"

namespace xgine { namespace graphics { namespace core {

class IndexBuffer
{
public:
    enum class IndexType
    {
        UINT16,
        UINT32
    };

    struct Info
    {
        uint32_t size;
        IndexType indexType;

        Info(uint32_t size_ = 0, IndexType indexType_ = IndexType::UINT32)
            : size(size_), indexType (indexType_) {}
    };

    static SPtr<IndexBuffer> Create(SPtr<Device> device, void* data, Info & info);
    static void Destroy(IndexBuffer* indexBuffer);

    Info GetInfo();
    vk::Buffer GetNative();
    SPtr<Buffer> GetBuffer();

    static vk::IndexType IndexTypeToVk(IndexType indexType);

private:
    IndexBuffer();
    ~IndexBuffer();

    Info info;
    SPtr<Buffer> buffer;

    SPtr<Device> device;

    DISALLOW_COPY_AND_ASSIGN(IndexBuffer);
};

} } }
