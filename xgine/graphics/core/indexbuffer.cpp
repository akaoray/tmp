#include "indexbuffer.h"

#include "device.h"

namespace xgine { namespace graphics { namespace core {

IndexBuffer::IndexBuffer()
{
    XDEBUG();
}

IndexBuffer::~IndexBuffer()
{
    XDEBUG();
}

SPtr<IndexBuffer> IndexBuffer::Create(SPtr<Device> device, void* data, Info & info)
{
    XDEBUG();

    SPtr<IndexBuffer> indexBuffer(new IndexBuffer(), IndexBuffer::Destroy);
    indexBuffer->device = device;
    indexBuffer->info = info;

    // Create tmp buffer
    Buffer::Info tmpBufferInfo(info.size, Buffer::Type::SRC, Buffer::Mode::HOST_VISIBLE);
    SPtr<Buffer> tmpBuffer = Buffer::Create(device, data, tmpBufferInfo);

    if(!tmpBuffer)
    {
        XMESSAGE("Invalid tmpBuffer");
        return nullptr;
    }

    // Create dst buffer
    Buffer::Info bufferInfo(info.size, Buffer::Type::INDEX | Buffer::Type::DST, Buffer::Mode::DEVICE_LOCAL);
    indexBuffer->buffer = Buffer::Create(device, nullptr, bufferInfo);

    if(!indexBuffer->buffer)
    {
        XMESSAGE("Invalid buffer");
        return nullptr;
    }

    if(!indexBuffer->buffer->CopyFromBuffer(tmpBuffer))
    {
        XMESSAGE("Invalid CopyFromBuffer");
        return nullptr;
    }

    return indexBuffer;
}

void IndexBuffer::Destroy(IndexBuffer* indexBuffer)
{
    XDEBUG();

    assert(indexBuffer != nullptr);

    delete indexBuffer;
}

IndexBuffer::Info IndexBuffer::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::Buffer IndexBuffer::GetNative()
{
    XDEBUG();

    return this->buffer->GetNative();
}

SPtr<Buffer> IndexBuffer::GetBuffer()
{
    XDEBUG();

    return this->buffer;
}

vk::IndexType IndexBuffer::IndexTypeToVk(IndexType indexType)
{
    XDEBUG();

    if(indexType == IndexType::UINT16) return vk::IndexType::eUint16;

    return vk::IndexType::eUint32;
}

} } }
