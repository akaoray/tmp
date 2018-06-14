#include "renderpass.h"

#include "device.h"

namespace xgine { namespace graphics { namespace core {

RenderPass::RenderPass()
{
    XDEBUG();
}

RenderPass::~RenderPass()
{
    XDEBUG();
}

SPtr<RenderPass> RenderPass::Create(SPtr<Device> device, Info & info)
{
    XDEBUG();

    SPtr<RenderPass> renderPass(new RenderPass(), RenderPass::Destroy);
    renderPass->device = device;
    renderPass->info = info;

    std::array<vk::AttachmentDescription, 1> attachments;
    std::array<vk::AttachmentReference, 1> attachmentReferences;

    // Color attachment
    attachments[0].format = info.format;
    attachments[0].loadOp = vk::AttachmentLoadOp::eClear;
    attachments[0].storeOp = vk::AttachmentStoreOp::eStore;
    attachments[0].initialLayout = vk::ImageLayout::eUndefined;
    attachments[0].finalLayout = vk::ImageLayout::ePresentSrcKHR;

    // Only one depth attachment, so put it first in the references
    vk::AttachmentReference& colorReference = attachmentReferences[0];
    colorReference.attachment = 0;
    colorReference.layout = vk::ImageLayout::eColorAttachmentOptimal;

    std::array<vk::SubpassDescription, 1> subpasses;
    {
        vk::SubpassDescription& subpass = subpasses[0];
        subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = attachmentReferences.data();
    }

    std::array<vk::SubpassDependency, 1> subpassDependencies;
    {
        vk::SubpassDependency& dependency = subpassDependencies[0];
        dependency.srcSubpass = 0;
        dependency.dstSubpass = VK_SUBPASS_EXTERNAL;
        dependency.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
        dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead;
        dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        dependency.srcStageMask = vk::PipelineStageFlagBits::eBottomOfPipe;
    }

    vk::RenderPassCreateInfo renderPassCreateInfo;
    renderPassCreateInfo.attachmentCount = (uint32_t)attachments.size();
    renderPassCreateInfo.pAttachments = attachments.data();
    renderPassCreateInfo.subpassCount = (uint32_t)subpasses.size();
    renderPassCreateInfo.pSubpasses = subpasses.data();
    renderPassCreateInfo.dependencyCount = (uint32_t)subpassDependencies.size();
    renderPassCreateInfo.pDependencies = subpassDependencies.data();
    renderPass->renderPass = device->GetNative().createRenderPass(renderPassCreateInfo);

    if(!renderPass->renderPass)
    {
        XMESSAGE("Invalid createRenderPass");
        return nullptr;
    }

    return renderPass;
}

void RenderPass::Destroy(RenderPass* renderPass)
{
    XDEBUG();

    assert(renderPass != nullptr);

    if(renderPass->renderPass) renderPass->device->GetNative().destroyRenderPass(renderPass->renderPass);

    delete renderPass;
}

RenderPass::Info RenderPass::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::RenderPass RenderPass::GetNative()
{
    XDEBUG();

    return this->renderPass;
}

} } }
