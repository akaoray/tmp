/*#include "pipeline.h"

#include "context.h"
#include "descriptorsetlayout.h"
#include "renderpass.h"
#include "shader.h"

namespace xgine {

namespace graphics {

Pipeline::Pipeline()
{
    XDEBUG();
}

Pipeline::~Pipeline()
{
    XDEBUG();
}

SPtr<Pipeline> Pipeline::Create(SPtr<Context> & context, Info & info)
{
    XDEBUG();

    SPtr<Pipeline> pipeline(new Pipeline(), Pipeline::Destroy);
    pipeline->context = context;
    pipeline->info = info;

    vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo;
    std::vector<vk::DescriptorSetLayout> descriptorSetLayouts;
    descriptorSetLayouts.resize(info.descriptorSetLayouts.size());
    for(uint32_t i = 0; i < info.descriptorSetLayouts.size(); i++)
    {
        descriptorSetLayouts[i] = info.descriptorSetLayouts[i]->GetNative();
    }
    pipelineLayoutCreateInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutCreateInfo.pSetLayouts = descriptorSetLayouts.data();
    pipeline->pipelineLayout = context->GetDevice().createPipelineLayout(pipelineLayoutCreateInfo);

    if(!pipeline->pipelineLayout)
    {
        XMESSAGE("Invalid createPipelineLayout");
        return nullptr;
    }

    vk::PipelineCacheCreateInfo pipelineCacheCreateInfo;
    pipeline->pipelineCache = context->GetDevice().createPipelineCache(pipelineCacheCreateInfo);

    if(!pipeline->pipelineCache)
    {
        XMESSAGE("Invalid createPipelineCache");
        return nullptr;
    }

    std::vector<vk::PipelineShaderStageCreateInfo> shaderStages;
    shaderStages.resize(info.shaders.size());
    for(uint32_t i = 0; i < info.shaders.size(); i++)
    {
        shaderStages[i].stage = info.shaders[i]->GetInfo().stage;
        shaderStages[i].pName = info.shaders[i]->GetInfo().entry.c_str();
        shaderStages[i].module = info.shaders[i]->GetNative();
    }

    vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo;

    graphicsPipelineCreateInfo.layout = pipeline->pipelineLayout;
    graphicsPipelineCreateInfo.renderPass = info.renderPass->GetNative();//this->renderPass->GetNative();

    graphicsPipelineCreateInfo.stageCount = shaderStages.size();//pipelineShaderStageCreateInfos.size();
    graphicsPipelineCreateInfo.pStages = shaderStages.data();//pipelineShaderStageCreateInfos.data();
    graphicsPipelineCreateInfo.pVertexInputState = &info.vertexInputState;//&pipelineVertexInputStateCreateInfo;
    graphicsPipelineCreateInfo.pInputAssemblyState = &info.inputAssemblyState;//&pipelineInputAssemblyStateCreateInfo;
    graphicsPipelineCreateInfo.pRasterizationState = &info.rasterizationState;//&pipelineRasterizationStateCreateInfo;
    graphicsPipelineCreateInfo.pColorBlendState = &info.colorBlendState;//&pipelineColorBlendStateCreateInfo;
    graphicsPipelineCreateInfo.pMultisampleState = &info.multisampleState;//&pipelineMultisampleStateCreateInfo;
    graphicsPipelineCreateInfo.pViewportState = &info.viewportState;//&pipelineViewportStateCreateInfo;
    graphicsPipelineCreateInfo.pDepthStencilState = &info.depthStencilState;//&pipelineDepthStencilStateCreateInfo;
    graphicsPipelineCreateInfo.pDynamicState = &info.dynamicState;//&pipelineDynamicStateCreateInfo;

    pipeline->pipeline = context->GetDevice().createGraphicsPipeline(pipeline->pipelineCache, graphicsPipelineCreateInfo);

    if(!pipeline->pipeline)
    {
        XMESSAGE("Invalid createGraphicsPipeline");
        return nullptr;
    }

    return pipeline;
}

void Pipeline::Destroy(Pipeline* pipeline)
{
    XDEBUG();

    assert(pipeline != nullptr);

    if(pipeline->pipelineLayout) pipeline->context->GetDevice().destroyPipelineLayout(pipeline->pipelineLayout);
    if(pipeline->pipelineCache) pipeline->context->GetDevice().destroyPipelineCache(pipeline->pipelineCache);
    if(pipeline->pipeline) pipeline->context->GetDevice().destroyPipeline(pipeline->pipeline);

    delete pipeline;
}

Pipeline::Info Pipeline::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::Pipeline Pipeline::GetNative()
{
    XDEBUG();

    return this->pipeline;
}

}

}

*/
