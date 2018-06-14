/*#include "descriptorsetlayout.h"

#include "context.h"

namespace xgine {

namespace graphics {

DescriptorSetLayout::DescriptorSetLayout()
{
    XDEBUG();
}

DescriptorSetLayout::~DescriptorSetLayout()
{
    XDEBUG();
}

SPtr<DescriptorSetLayout> DescriptorSetLayout::Create(SPtr<Context> & context, Info & info)
{
    XDEBUG();

    SPtr<DescriptorSetLayout> descriptorSetLayout(new DescriptorSetLayout(), DescriptorSetLayout::Destroy);
    descriptorSetLayout->context = context;
    descriptorSetLayout->info = info;

    vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo;
    descriptorSetLayoutCreateInfo.bindingCount = info.descriptorSetLayoutBindings.size();
    descriptorSetLayoutCreateInfo.pBindings = info.descriptorSetLayoutBindings.data();

    descriptorSetLayout->descriptorSetLayout = context->GetDevice().createDescriptorSetLayout(descriptorSetLayoutCreateInfo);

    if(!descriptorSetLayout->descriptorSetLayout)
    {
        XMESSAGE("Invalid createDescriptorSetLayout");
        return nullptr;
    }

    return descriptorSetLayout;
}

void DescriptorSetLayout::Destroy(DescriptorSetLayout* descriptorSetLayout)
{
    XDEBUG();

    assert(descriptorSetLayout != nullptr);

    if(descriptorSetLayout->descriptorSetLayout) descriptorSetLayout->context->GetDevice().destroyDescriptorSetLayout(descriptorSetLayout->descriptorSetLayout);

    delete descriptorSetLayout;
}

DescriptorSetLayout::Info DescriptorSetLayout::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::DescriptorSetLayout DescriptorSetLayout::GetNative()
{
    XDEBUG();

    return this->descriptorSetLayout;
}

}

}

*/
