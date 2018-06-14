#include "buffer.h"

#include "device.h"

namespace xgine { namespace graphics { namespace core {

Buffer::Buffer()
{
    XDEBUG();
}

Buffer::~Buffer()
{
    XDEBUG();
}

SPtr<Buffer> Buffer::Create(SPtr<Device> device, void* data, Info & info)
{
    XDEBUG();

    SPtr<Buffer> buffer(new Buffer(), Buffer::Destroy);
    buffer->device = device;
    buffer->info = info;

    // Create buffer
    vk::BufferCreateInfo bufferCreateInfo;
    bufferCreateInfo.size = info.size;
    bufferCreateInfo.usage = Buffer::TypeToVk(info.type);
    buffer->buffer = device->GetNative().createBuffer(bufferCreateInfo);

    if(!buffer->buffer)
    {
        XMESSAGE("Invalid createBuffer");
        return nullptr;
    }

    // Create buffer memory
    vk::MemoryAllocateInfo memoryAllocateInfo;
    vk::MemoryRequirements memoryRequirements;
    memoryRequirements = device->GetNative().getBufferMemoryRequirements(buffer->buffer);
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex = device->GetInfo().gpu.getMemoryType(memoryRequirements.memoryTypeBits, Buffer::ModeToVk(info.mode));
    buffer->bufferMemory = device->GetNative().allocateMemory(memoryAllocateInfo);

    if(!buffer->bufferMemory)
    {
        XMESSAGE("Invalid allocateMemory");
        return nullptr;
    }

    if(data != nullptr && (info.mode & Mode::HOST_VISIBLE))
    {
        // Copy data to tmp buffer memory
        void* mapMem = device->GetNative().mapMemory(buffer->bufferMemory, 0, info.size, vk::MemoryMapFlags());
        memcpy(mapMem, data, info.size);
        device->GetNative().unmapMemory(buffer->bufferMemory);
    }

    // Bind memory to buffer
    device->GetNative().bindBufferMemory(buffer->buffer, buffer->bufferMemory, 0);

    return buffer;
}

void Buffer::Destroy(Buffer* buffer)
{
    XDEBUG();

    assert(buffer != nullptr);

    if(buffer->bufferMemory) buffer->device->GetNative().freeMemory(buffer->bufferMemory);
    if(buffer->buffer) buffer->device->GetNative().destroyBuffer(buffer->buffer);

    delete buffer;
}

Buffer::Info Buffer::GetInfo()
{
   XDEBUG();

   return this->info;
}

vk::Buffer Buffer::GetNative()
{
    XDEBUG();

    return this->buffer;
}

void* Buffer::Map(uint32_t offset, uint32_t size)
{
    XDEBUG();

    if(!(this->info.mode & Mode::HOST_VISIBLE))
    {
        XMESSAGE("Invalid buffer mode");
        return nullptr;
    }

    if(offset + size > this->info.size)
    {
        XMESSAGE("Invalid buffer offset or size");
        return nullptr;
    }

    return this->device->GetNative().mapMemory(this->bufferMemory, offset, size, vk::MemoryMapFlags());
}

void Buffer::Unmap()
{
    XDEBUG();

    if(!(this->info.mode & Mode::HOST_VISIBLE))
    {
        XMESSAGE("Invalid buffer mode");
        return;
    }

    this->device->GetNative().unmapMemory(this->bufferMemory);
}

bool Buffer::CopyFromData(void* data, uint32_t offset, uint32_t size)
{
    XDEBUG();

    if(!(this->info.mode & Mode::HOST_VISIBLE))
    {
        XMESSAGE("Invalid buffer mode");
        return false;
    }

    if(data == nullptr)
    {
        XMESSAGE("Invalid buffer data");
        return false;
    }

    if(offset + size > this->info.size)
    {
        XMESSAGE("Invalid buffer offset or size");
        return false;
    }

    void* mapMem = this->device->GetNative().mapMemory(this->bufferMemory, offset, size, vk::MemoryMapFlags());
    memcpy(mapMem, data, size);
    this->device->GetNative().unmapMemory(this->bufferMemory);

    return true;
}

bool Buffer::CopyFromBuffer(SPtr<Buffer> buffer)
{
    XDEBUG();

    if(!(this->info.type & Type::DST))
    {
        XMESSAGE("Invalid buffer DST type");
        return false;
    }

    if(!(buffer->GetInfo().type & Type::SRC))
    {
        XMESSAGE("Invalid buffer SRC type");
        return false;
    }

    if(this->info.size != buffer->GetInfo().size)
    {
        XMESSAGE("Invalid buffer sizes not equal");
        return false;
    }

    vk::CommandBufferAllocateInfo commandBufferAllocateInfo;
    commandBufferAllocateInfo.commandPool = device->GetCommandPool();
    commandBufferAllocateInfo.level = vk::CommandBufferLevel::ePrimary;
    commandBufferAllocateInfo.commandBufferCount = 1;
    vk::CommandBuffer commandBuffer = device->GetNative().allocateCommandBuffers(commandBufferAllocateInfo)[0];

    if(!commandBuffer)
    {
        XMESSAGE("Invalid allocateCommandBuffers");
        return false;
    }

    vk::CommandBufferBeginInfo commandBufferBeginInfo;
    vk::BufferCopy bufferCopy;

    commandBuffer.begin(commandBufferBeginInfo);
    bufferCopy.size = this->info.size;
    commandBuffer.copyBuffer(buffer->GetNative(), this->buffer, bufferCopy);

    vk::SubmitInfo submitInfo;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vk::Fence fence;
    this->device->GetGraphicsQueue().submit(submitInfo, fence);
    this->device->GetGraphicsQueue().waitIdle();

    this->device->GetNative().freeCommandBuffers(device->GetCommandPool(), commandBuffer);

    return true;
}

vk::BufferUsageFlags Buffer::TypeToVk(Flags type)
{
    XDEBUG();

    vk::BufferUsageFlags usage;
    if(type & Type::VERTEX) usage |= vk::BufferUsageFlagBits::eVertexBuffer;
    if(type & Type::INDEX) usage |= vk::BufferUsageFlagBits::eVertexBuffer;
    if(type & Type::UNIFORM) usage |= vk::BufferUsageFlagBits::eVertexBuffer;
    if(type & Type::DST) usage |= vk::BufferUsageFlagBits::eVertexBuffer;
    if(type & Type::SRC) usage |= vk::BufferUsageFlagBits::eVertexBuffer;

    return usage;
}

vk::MemoryPropertyFlags Buffer::ModeToVk(Flags mode)
{
    XDEBUG();

    vk::MemoryPropertyFlags memoryProperty;
    if(mode & Mode::DEVICE_LOCAL) memoryProperty |= vk::MemoryPropertyFlagBits::eDeviceLocal;
    if(mode & Mode::HOST_VISIBLE) memoryProperty |= vk::MemoryPropertyFlagBits::eHostVisible;
    if(mode & Mode::HOST_COHERENT) memoryProperty |= vk::MemoryPropertyFlagBits::eHostCoherent;

    return memoryProperty;
}

} } }
