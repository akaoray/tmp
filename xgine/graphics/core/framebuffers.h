/*#ifndef FRAMEBUFFERS_H
#define FRAMEBUFFERS_H

#include "xgine/base.h"

namespace xgine {

namespace graphics {

class Context;

class Framebuffers
{
public:
    struct Info
    {
        uint32_t width;
        uint32_t height;
        vk::RenderPass renderPass;
        std::vector<vk::ImageView> imageViews;

        Info(uint32_t width_ = 0, uint32_t height_ = 0, vk::RenderPass renderPass_ = vk::RenderPass(), std::vector<vk::ImageView> imageViews_ = {})
            : width(width_), height(height_), renderPass(renderPass_), imageViews(imageViews_) {}
    };

    static std::shared_ptr<Framebuffers> Create(std::shared_ptr<Context> & context, Info & info);
    static void Destroy(Framebuffers* framebuffers);

    Info GetInfo();
    std::vector<vk::Framebuffer> GetNative();

private:
    Framebuffers();
    ~Framebuffers();

    Info info;
    std::vector<vk::Framebuffer> framebuffers;

    std::shared_ptr<Context> context;

    DISALLOW_COPY_AND_ASSIGN(Framebuffers);
};

}

}

#endif // FRAMEBUFFER_H
*/
