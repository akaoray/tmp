#include "shader.h"

#include "device.h"

namespace xgine { namespace graphics { namespace core {

Shader::Shader()
{
    XDEBUG();
}

Shader::~Shader()
{
    XDEBUG();
}

SPtr<Shader> Shader::Create(SPtr<Device> device, void* data, Info & info)
{
    XDEBUG();

    SPtr<Shader> shader(new Shader(), Shader::Destroy);
    shader->device = device;
    shader->info = info;

    switch(info.type)
    {
    case Type::SPIRV:
        shader->shaderModule = device->GetNative().createShaderModule({ {}, info.size, (const uint32_t*)data });
        if(!shader->shaderModule)
        {
            XMESSAGE("Invalid createShaderModule");
            return nullptr;
        }

        break;
    /*case SrcType::T_GLSL:
        file = fs::File::Create(info.file, fs::File::Mode::M_TEXT);
        if(!file)
        {
            XMESSAGE("Invalid load shader file " + info.file);
            return nullptr;
        }

        char* code = file->GetData();
        vk::ShaderModuleCreateInfo shaderModuleCreateInfo;
        shaderModuleCreateInfo.codeSize = 3 * sizeof(uint32_t) + file->GetSize() + 1;
        shaderModuleCreateInfo.pCode = (uint32_t*)malloc(shaderModuleCreateInfo.codeSize);

        // Magic SPV number
        ((uint32_t *)shaderModuleCreateInfo.pCode)[0] = 0x07230203;
        ((uint32_t *)shaderModuleCreateInfo.pCode)[1] = 0;
        ((uint32_t *)shaderModuleCreateInfo.pCode)[2] = (uint32_t)info.type;
        memcpy(((uint32_t *)shaderModuleCreateInfo.pCode + 3), code, file->GetSize() + 1);

        shader->shader = context->GetDevice().createShaderModule(shaderModuleCreateInfo);
        free((void*)shaderModuleCreateInfo.pCode);

        if(!shader->shader)
        {
            XMESSAGE("Invalid createShaderModule for " + info.file);
            return nullptr;
        }
        break;*/
    }

    return shader;
}

void Shader::Destroy(Shader* shader)
{
    XDEBUG();

    assert(shader != nullptr);

    if(shader->shaderModule) shader->device->GetNative().destroyShaderModule(shader->shaderModule);

    delete shader;
}

Shader::Info Shader::GetInfo()
{
    XDEBUG();

    return this->info;
}

vk::ShaderModule Shader::GetNative()
{
    XDEBUG();

    return this->shaderModule;
}

vk::ShaderStageFlagBits Shader::StageToVk(Stage stage)
{
    if(stage == Stage::VERTEX) return vk::ShaderStageFlagBits::eVertex;
    return vk::ShaderStageFlagBits::eFragment;
}

} } }

