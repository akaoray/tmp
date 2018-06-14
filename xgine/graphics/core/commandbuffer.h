/*#ifndef COMMANDBUFFER_H
#define COMMANDBUFFER_H

#include "xgine/base.h"

namespace xgine {

namespace graphics {

class CommandBuffer
{
public:
    struct Info
    {
        vk::CommandBufferAllocateInfo allocateInfo;

        Info(vk::CommandBufferAllocateInfo allocateInfo_ = {})
            : allocateInfo(allocateInfo_){}
    };

private:
    CommandBuffer();
    ~CommandBuffer();

    vk::CommandBuffer commandBuffer;

    DISALLOW_COPY_AND_ASSIGN(CommandBuffer);
};

}

}

#endif // COMMANDBUFFER_H*/
