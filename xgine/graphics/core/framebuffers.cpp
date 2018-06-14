/*#include "framebuffers.h"

#include "context.h"

namespace xgine {

namespace graphics {

Framebuffers::Framebuffers()
{
    XDEBUG();
}

Framebuffers::~Framebuffers()
{
    XDEBUG();
}

std::shared_ptr<Framebuffers> Framebuffers::Create(std::shared_ptr<Context> & context, Info & info)
{
    XDEBUG();

    std::shared_ptr<Framebuffers> framebuffers(new Framebuffers(), Framebuffers::Destroy);
    framebuffers->context = context;
    framebuffers->info = info;

    vk::FramebufferCreateInfo framebufferCreateInfo;
    framebufferCreateInfo.renderPass = info.renderPass;
    framebufferCreateInfo.attachmentCount = 1;//(uint32_t)info.imageViews.size();
    //framebufferCreateInfo.pAttachments = info.imageViews.data();
    framebufferCreateInfo.width = info.width;
    framebufferCreateInfo.height = info.height;
    framebufferCreateInfo.layers = 1;

    std::array<vk::ImageView, 1> attachments;
    framebufferCreateInfo.pAttachments = attachments.data();
    framebuffers->framebuffers.resize(info.imageViews.size());
    for(uint32_t i = 0; i < info.imageViews.size(); i++)
    {
        attachments[0] = info.imageViews[i];
        framebuffers->framebuffers[i] = context->GetDevice().createFramebuffer(framebufferCreateInfo);

        if(!framebuffers->framebuffers[i])
        {
            XMESSAGE("Invalid createFramebuffer");
            return nullptr;
        }
    }

    return framebuffers;
}

void Framebuffers::Destroy(Framebuffers* framebuffers)
{
    XDEBUG();

    assert(framebuffers != nullptr);

    for(uint32_t i = 0; i < framebuffers->framebuffers.size(); i++)
    {
        if(framebuffers->framebuffers[i]) framebuffers->context->GetDevice().destroyFramebuffer(framebuffers->framebuffers[i]);
    }

    delete framebuffers;
}

Framebuffers::Info Framebuffers::GetInfo()
{
    XDEBUG();

    return this->info;
}

std::vector<vk::Framebuffer> Framebuffers::GetNative()
{
    XDEBUG();

    return this->framebuffers;
}

}

}

*/
