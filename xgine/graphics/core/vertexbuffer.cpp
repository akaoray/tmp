#include "vertexbuffer.h"

#include "device.h"

namespace xgine { namespace graphics { namespace core {

VertexBuffer::VertexBuffer()
{
    XDEBUG();
}

VertexBuffer::~VertexBuffer()
{
    XDEBUG();
}

SPtr<VertexBuffer> VertexBuffer::Create(SPtr<Device> device, void* data, Info & info)
{
    XDEBUG();

    SPtr<VertexBuffer> vertexBuffer(new VertexBuffer(), VertexBuffer::Destroy);
    vertexBuffer->device = device;
    vertexBuffer->info = info;

    // Create tmp buffer
    Buffer::Info tmpBufferInfo(info.size, Buffer::Type::SRC, Buffer::Mode::HOST_VISIBLE);
    SPtr<Buffer> tmpBuffer = Buffer::Create(device, data, tmpBufferInfo);

    if(!tmpBuffer)
    {
        XMESSAGE("Invalid tmpBuffer");
        return nullptr;
    }

    // Create dst buffer
    Buffer::Info bufferInfo(info.size, Buffer::Type::VERTEX | Buffer::Type::DST, Buffer::Mode::DEVICE_LOCAL);
    vertexBuffer->buffer = Buffer::Create(device, nullptr, bufferInfo);

    if(!vertexBuffer->buffer)
    {
        XMESSAGE("Invalid buffer");
        return nullptr;
    }

    if(!vertexBuffer->buffer->CopyFromBuffer(tmpBuffer))
    {
        XMESSAGE("Invalid CopyFromBuffer");
        return nullptr;
    }

    return vertexBuffer;
}

void VertexBuffer::Destroy(VertexBuffer* vertexBuffer)
{
    XDEBUG();

    assert(vertexBuffer != nullptr);

    delete vertexBuffer;
}

VertexBuffer::Info VertexBuffer::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::Buffer VertexBuffer::GetNative()
{
    XDEBUG();

    return this->buffer->GetNative();
}

SPtr<Buffer> VertexBuffer::GetBuffer()
{
    XDEBUG();

    return this->buffer;
}

} } }
