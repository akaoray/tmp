/*#include "descriptorpool.h"

#include "context.h"

namespace xgine {

namespace graphics {

DescriptorPool::DescriptorPool()
{
    XDEBUG();
}

DescriptorPool::~DescriptorPool()
{
    XDEBUG();
}

SPtr<DescriptorPool> DescriptorPool::Create(SPtr<Context> & context, Info & info)
{
    XDEBUG();
    SPtr<DescriptorPool> descriptorPool(new DescriptorPool(), DescriptorPool::Destroy);
    descriptorPool->context = context;
    descriptorPool->info = info;

    vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo;
    descriptorPoolCreateInfo.poolSizeCount = info.descriptorPoolSizes.size();
    descriptorPoolCreateInfo.pPoolSizes = info.descriptorPoolSizes.data();
    descriptorPoolCreateInfo.maxSets = info.maxSets;

    descriptorPool->descriptorPool = context->GetDevice().createDescriptorPool(descriptorPoolCreateInfo);

    if(!descriptorPool->descriptorPool)
    {
        XMESSAGE("Invalid createDescriptorPool");
        return nullptr;
    }

    return descriptorPool;
}

void DescriptorPool::Destroy(DescriptorPool* descriptorPool)
{
    XDEBUG();

    assert(descriptorPool != nullptr);

    if(descriptorPool->descriptorPool) descriptorPool->context->GetDevice().destroyDescriptorPool(descriptorPool->descriptorPool);

    delete descriptorPool;
}

DescriptorPool::Info DescriptorPool::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::DescriptorPool DescriptorPool::GetNative()
{
    XDEBUG();

    return this->descriptorPool;
}

}

}

*/
