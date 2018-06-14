#include "uniformbuffer.h"

#include "device.h"

namespace xgine { namespace graphics { namespace core {

UniformBuffer::UniformBuffer()
{
    XDEBUG();
}

UniformBuffer::~UniformBuffer()
{
    XDEBUG();
}

SPtr<UniformBuffer> UniformBuffer::Create(SPtr<Device> device, void* data, Info & info)
{
    XDEBUG();

    SPtr<UniformBuffer> uniformBuffer(new UniformBuffer(), UniformBuffer::Destroy);
    uniformBuffer->device = device;
    uniformBuffer->info = info;

    // Create buffer
    Buffer::Info bufferInfo(info.size, Buffer::Type::UNIFORM, Buffer::Mode::HOST_VISIBLE | Buffer::Mode::HOST_COHERENT);
    uniformBuffer->buffer = Buffer::Create(device, data, bufferInfo);

    if(!uniformBuffer->buffer)
    {
        XMESSAGE("Invalid buffer");
        return nullptr;
    }

    return uniformBuffer;
}

void UniformBuffer::Destroy(UniformBuffer* uniformBuffer)
{
    XDEBUG();

    assert(uniformBuffer != nullptr);

    delete uniformBuffer;
}

UniformBuffer::Info UniformBuffer::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::Buffer UniformBuffer::GetNative()
{
    XDEBUG();

    return this->buffer->GetNative();
}

SPtr<Buffer> UniformBuffer::GetBuffer()
{
    XDEBUG();

    return this->buffer;
}

bool UniformBuffer::Update(void* data, uint32_t offset, uint32_t size)
{
    return this->buffer->CopyFromData(data, offset, size);
}

} } }
