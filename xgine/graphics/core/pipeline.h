/*#ifndef PIPELINE_H
#define PIPELINE_H

#include "xgine/base.h"

namespace xgine {

namespace graphics {

class Context;
class DescriptorSetLayout;
class RenderPass;
class Shader;

class Pipeline
{
public:
    struct Info
    {
        std::vector<SPtr<DescriptorSetLayout>> descriptorSetLayouts; //1
        SPtr<RenderPass> renderPass; //2
        vk::PipelineInputAssemblyStateCreateInfo inputAssemblyState; //3
        vk::PipelineRasterizationStateCreateInfo rasterizationState; //4
        vk::PipelineColorBlendStateCreateInfo colorBlendState; //5
        vk::PipelineViewportStateCreateInfo viewportState; //6
        vk::PipelineDynamicStateCreateInfo dynamicState; //7
        vk::PipelineDepthStencilStateCreateInfo depthStencilState; //8
        vk::PipelineMultisampleStateCreateInfo multisampleState; //9
        std::vector<SPtr<Shader>> shaders; //10
        vk::PipelineVertexInputStateCreateInfo vertexInputState; //11

        Info(std::vector<SPtr<DescriptorSetLayout>> descriptorSetLayouts_ = {}, SPtr<RenderPass> renderPass_ = nullptr, vk::PipelineInputAssemblyStateCreateInfo inputAssemblyState_ = {},
             vk::PipelineRasterizationStateCreateInfo rasterizationState_ = {}, vk::PipelineColorBlendStateCreateInfo colorBlendState_ = {}, vk::PipelineViewportStateCreateInfo viewportState_ = {},
             vk::PipelineDynamicStateCreateInfo dynamicState_ = {}, vk::PipelineDepthStencilStateCreateInfo depthStencilState_ = {}, vk::PipelineMultisampleStateCreateInfo multisampleState_ = {},
             std::vector<SPtr<Shader>> shaders_ = {}, vk::PipelineVertexInputStateCreateInfo vertexInputState_ = {})
            : descriptorSetLayouts(descriptorSetLayouts_), renderPass(renderPass_), inputAssemblyState(inputAssemblyState_), rasterizationState(rasterizationState_),
              colorBlendState(colorBlendState_), viewportState(viewportState_), dynamicState(dynamicState_), depthStencilState(depthStencilState_),
              multisampleState(multisampleState_), shaders(shaders_), vertexInputState(vertexInputState_) {}
    };

    static SPtr<Pipeline> Create(SPtr<Context> & context, Info & info);
    static void Destroy(Pipeline* pipeline);

    Info GetInfo();
    vk::Pipeline GetNative();

private:
    Pipeline();
    ~Pipeline();

    Info info;
    vk::PipelineLayout pipelineLayout;
    vk::PipelineCache pipelineCache;
    vk::Pipeline pipeline;

    SPtr<Context> context;
};

}

}

#endif // PIPELINE_H
*/
