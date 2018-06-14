/*#ifndef DESCRIPTORPOOL_H
#define DESCRIPTORPOOL_H

#include "xgine/base.h"

namespace xgine {

namespace graphics {

class Context;

class DescriptorPool
{
public:
    struct Info
    {
        std::vector<vk::DescriptorPoolSize> descriptorPoolSizes;
        uint32_t maxSets;

        Info(std::vector<vk::DescriptorPoolSize> descriptorPoolSizes_ = {
            {vk::DescriptorType::eCombinedImageSampler, sMaxSampledImages},
            {vk::DescriptorType::eUniformBuffer, sMaxUniformBuffers},
            {vk::DescriptorType::eStorageImage, sMaxImages},
            {vk::DescriptorType::eUniformTexelBuffer, sMaxSampledBuffers},
            {vk::DescriptorType::eStorageTexelBuffer, sMaxBuffers},
            {vk::DescriptorType::eStorageBuffer, sMaxBuffers}
    }, uint32_t maxSets_ = sMaxSets)
            : descriptorPoolSizes(descriptorPoolSizes_), maxSets(maxSets_) {}
    };

    static SPtr<DescriptorPool> Create(SPtr<Context> & context, Info & info);
    static void Destroy(DescriptorPool* descriptorPool);

    Info GetInfo();
    vk::DescriptorPool GetNative();

private:
    DescriptorPool();
    ~DescriptorPool();

    Info info;
    vk::DescriptorPool descriptorPool;

    SPtr<Context> context;

    static const uint32_t sMaxSets = 8192;
    static const uint32_t sMaxSampledImages = 4096;
    static const uint32_t sMaxImages = 2048;
    static const uint32_t sMaxSampledBuffers = 2048;
    static const uint32_t sMaxBuffers = 2048;
    static const uint32_t sMaxUniformBuffers = 2048;

    DISALLOW_COPY_AND_ASSIGN(DescriptorPool);
};

}

}

#endif // DESCRIPTORPOOL_H*/

