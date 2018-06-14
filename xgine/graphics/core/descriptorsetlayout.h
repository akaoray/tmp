/*#ifndef DESCRIPTORSETLAYOUT_H
#define DESCRIPTORSETLAYOUT_H

#include "xgine/base.h"

namespace xgine {

namespace graphics {

class Context;

class DescriptorSetLayout
{
public:
    struct Info
    {
        std::vector<vk::DescriptorSetLayoutBinding> descriptorSetLayoutBindings;

        Info(std::vector<vk::DescriptorSetLayoutBinding> descriptorSetLayoutBindings_ = {})
            : descriptorSetLayoutBindings(descriptorSetLayoutBindings_) {}
    };

    static SPtr<DescriptorSetLayout> Create(SPtr<Context> & context, Info & info);
    static void Destroy(DescriptorSetLayout* descriptorSetLayout);

    Info GetInfo();
    vk::DescriptorSetLayout GetNative();

private:
    DescriptorSetLayout();
    ~DescriptorSetLayout();

    Info info;
    vk::DescriptorSetLayout descriptorSetLayout;

    SPtr<Context> context;

    DISALLOW_COPY_AND_ASSIGN(DescriptorSetLayout);
};

}

}

#endif // DESCRIPTORSETLAYOUT_H
*/
