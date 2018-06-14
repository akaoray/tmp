
#include "xgine/app.h"

#include "xgine/fs/file.h"

#include "xgine/graphics/core/buffer.h"
#include "xgine/graphics/core/descriptorpool.h"
#include "xgine/graphics/core/descriptorsetlayout.h"
#include "xgine/graphics/core/device.h"
#include "xgine/graphics/core/framebuffers.h"
#include "xgine/graphics/core/gpulist.h"
#include "xgine/graphics/core/indexbuffer.h"
#include "xgine/graphics/core/instance.h"
#include "xgine/graphics/core/pipeline.h"
#include "xgine/graphics/core/renderpass.h"
#include "xgine/graphics/core/shader.h"
#include "xgine/graphics/core/surface.h"
#include "xgine/graphics/core/swapchain.h"
#include "xgine/graphics/core/uniformbuffer.h"
#include "xgine/graphics/core/vertexbuffer.h"
#include "xgine/graphics/core/window.h"

using namespace xgine::graphics::core;
using namespace xgine::fs;

int main()
{
    XDEBUG();

    // Create main app
    auto app = xgine::App::Create();

    // Create window
    Window::Info windowInfo("title", 800, 600);
    auto window = Window::Create(windowInfo);

    // Create engine instance
    Instance::Info instanceInfo = {"app", 1, "engine", 1};
    auto instance = Instance::Create(instanceInfo);

    auto surface = Surface::Create(instance, window);

    auto gpuList = GpuList::Create(instance, surface);

    std::cout<<gpuList->GetList().size()<<std::endl;

    Device::Info deviceInfo(gpuList->PickGpu(), GetRequiredDeviceExtensions());
    auto device = Device::Create(deviceInfo);

    // Create engine context


    // Create swap chain
    SwapChain::Info swapChainInfo;
    auto swapChain = SwapChain::Create(surface, device, swapChainInfo);

    // Create vertex buffer
    struct Vertex {
        float pos[3];
        float col[3];
    };

    // Setup vertices
    std::vector<Vertex> VB = { { { 1.0f, 1.0f, 0.0f },
                                 { 1.0f,
                                   0.0f,
                                   0.0f } },
                               { { -1.0f, 1.0f, 0.0f },
                                 { 0.0f,
                                   1.0f,
                                   0.0f } },
                               { { 0.0f, -1.0f, 0.0f },
                                 { 0.0f,
                                   0.0f,
                                   1.0f } } };
    uint32_t VBSize = (uint32_t)(VB.size() * sizeof(Vertex));

    VertexBuffer::Info VBI(VBSize, sizeof(Vertex), {});
    auto vertexBuffer = VertexBuffer::Create(device, VB.data(), VBI);

    // Create index buffer
    std::vector<uint32_t> IB = {0, 1, 2};
    uint32_t IBSize = (uint32_t)(IB.size() * sizeof(uint32_t));

    IndexBuffer::Info IBI(IBSize, IndexBuffer::IndexType::UINT32);
    auto indexBuffer = IndexBuffer::Create(device, IB.data(), IBI);

    // Create uniform buffer
    struct uboVS{
        glm::mat4 projectionMatrix;
        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
    };

    uboVS uvs;

    UniformBuffer::Info UBI(sizeof(uboVS));
    auto uniformBuffer = UniformBuffer::Create(device, &uvs, UBI);

    RenderPass::Info renderPassInfo(swapChain->GetFormat());
    auto renderPass = RenderPass::Create(device, renderPassInfo);


    SPtr<File> VSFile = File::Create("/home/anxu/anxu/shaders/vert.spv", File::Mode::M_BIN);
    Shader::Info VSInfo(Shader::Type::SPIRV, Shader::Stage::VERTEX, VSFile->GetSize(), "main");
    auto VS = Shader::Create(device, VSFile->GetData(), VSInfo);

    SPtr<File> FSFile = File::Create("/home/anxu/anxu/shaders/frag.spv", File::Mode::M_BIN);
    Shader::Info FSInfo(Shader::Type::SPIRV, Shader::Stage::FRAGMENT, FSFile->GetSize(), "main");
    auto FS = Shader::Create(device, FSFile->GetData(), FSInfo);

    /*

    // Create framebuffers
    Framebuffers::Info framebuffersInfo(windowInfo.width, windowInfo.height, renderPass->GetNative(), swapChain->GetImageViews());
    auto framebuffers = Framebuffers::Create(context, framebuffersInfo);

    // Create descriptor pool
    DescriptorPool::Info DPInfo({{vk::DescriptorType::eUniformBuffer, 1}}, 1);
    auto DP = DescriptorPool::Create(context, DPInfo);

    // Create descriptor set layout
    DescriptorSetLayout::Info DSLInfo({{0, vk::DescriptorType::eUniformBuffer, 1, vk::ShaderStageFlagBits::eVertex}});
    auto DSL = DescriptorSetLayout::Create(context, DSLInfo);

    // Create pipeline
    Pipeline::Info PI;
    PI.descriptorSetLayouts = { DSL }; //1
    PI.renderPass = renderPass; //2

    //inputAssemblyState
    PI.inputAssemblyState.topology = vk::PrimitiveTopology::eTriangleList; //3

    //rasterizationState
    PI.rasterizationState.polygonMode = vk::PolygonMode::eFill; //4
    PI.rasterizationState.cullMode = vk::CullModeFlagBits::eNone;
    PI.rasterizationState.frontFace = vk::FrontFace::eCounterClockwise;
    PI.rasterizationState.depthClampEnable = VK_FALSE;
    PI.rasterizationState.rasterizerDiscardEnable = VK_FALSE;
    PI.rasterizationState.depthBiasEnable = VK_FALSE;
    PI.rasterizationState.lineWidth = 1.0f;

    //colorBlendState
    vk::PipelineColorBlendAttachmentState blendAttachmentState[1] = {}; //5
    blendAttachmentState[0].colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    blendAttachmentState[0].blendEnable = VK_FALSE;
    PI.colorBlendState.attachmentCount = 1;
    PI.colorBlendState.pAttachments = blendAttachmentState;

    //viewportState
    PI.viewportState.viewportCount = 1; //6
    PI.viewportState.scissorCount = 1;

    //dynamicState
    std::vector<vk::DynamicState> dynamicStateEnables; //7
    dynamicStateEnables.push_back(vk::DynamicState::eViewport);
    dynamicStateEnables.push_back(vk::DynamicState::eScissor);
    PI.dynamicState.dynamicStateCount = (uint32_t)dynamicStateEnables.size();
    PI.dynamicState.pDynamicStates = dynamicStateEnables.data();

    //depthStencilState
    PI.depthStencilState.depthTestEnable = VK_FALSE; //8
    PI.depthStencilState.depthWriteEnable = VK_FALSE;
    PI.depthStencilState.stencilTestEnable = VK_FALSE;

    //multisampleState
    PI.multisampleState.pSampleMask = NULL; //9
    PI.multisampleState.rasterizationSamples = vk::SampleCountFlagBits::e1;

    PI.shaders = {VS, FS}; //10

    // Binding description
    std::vector<vk::VertexInputBindingDescription> bindingDescriptions;
    bindingDescriptions.resize(1);
    bindingDescriptions[0].binding = 0;
    bindingDescriptions[0].stride = sizeof(Vertex);
    bindingDescriptions[0].inputRate = vk::VertexInputRate::eVertex;

    // Attribute descriptions
    // Describes memory layout and shader attribute locations
    std::vector<vk::VertexInputAttributeDescription> attributeDescriptions;
    attributeDescriptions.resize(2);
    // Location 0 : Position
    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = vk::Format::eR32G32B32Sfloat;
    attributeDescriptions[0].offset = 0;
    // Location 1 : Color
    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = vk::Format::eR32G32B32Sfloat;
    attributeDescriptions[1].offset = sizeof(float) * 3;

    PI.vertexInputState.vertexBindingDescriptionCount = (uint32_t)bindingDescriptions.size(); //11
    PI.vertexInputState.pVertexBindingDescriptions = bindingDescriptions.data();
    PI.vertexInputState.vertexAttributeDescriptionCount = (uint32_t)attributeDescriptions.size();
    PI.vertexInputState.pVertexAttributeDescriptions = attributeDescriptions.data();

    auto P = Pipeline::Create(context, PI);*/

    return 0;
}

