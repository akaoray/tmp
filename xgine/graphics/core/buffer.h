#pragma once

#include "base.h"

namespace xgine { namespace graphics { namespace core {

class Buffer
{
public:
    enum Type : Flags
    {
        VERTEX  = 0x1,
        INDEX   = 0x2,
        UNIFORM = 0x4,
        DST     = 0x8,
        SRC     = 0x10
    };

    enum Mode : Flags
    {
        DEVICE_LOCAL = 0x1,
        HOST_VISIBLE = 0x2,
        HOST_COHERENT = 0x4
    };

    struct Info
    {
        uint32_t size;
        Flags type;
        Flags mode;

        Info(uint32_t size_ = 0, Flags type_ = Type::VERTEX | Type::DST, Flags mode_ = Mode::DEVICE_LOCAL)
            : size(size_), type(type_), mode(mode_) {}
    };

    static SPtr<Buffer> Create(SPtr<Device> device, void* data, Info & info);
    static void Destroy(Buffer* buffer);

    Info GetInfo();
    vk::Buffer GetNative();

    void* Map(uint32_t offset, uint32_t size);
    void Unmap();

    bool CopyFromData(void* data, uint32_t offset, uint32_t size);
    bool CopyFromBuffer(SPtr<Buffer> buffer);

    static vk::BufferUsageFlags TypeToVk(Flags type);
    static vk::MemoryPropertyFlags ModeToVk(Flags mode);

private:
    Buffer();
    ~Buffer();

    Info info;
    vk::Buffer buffer;
    vk::DeviceMemory bufferMemory;

    SPtr<Device> device;

    DISALLOW_COPY_AND_ASSIGN(Buffer);
};

} } }
