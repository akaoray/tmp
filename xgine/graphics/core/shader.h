#pragma once

#include "base.h"

namespace xgine { namespace graphics { namespace core {

class Shader
{
public:
    enum class Type
    {
        SPIRV
    };

    enum class Stage
    {
        VERTEX,
        FRAGMENT
    };

    struct Info
    {
        Type type;
        Stage stage;
        uint32_t size;
        std::string entry;

        Info(Type type_ = Type::SPIRV, Stage stage_ = Stage::VERTEX, uint32_t size_ = 0, std::string entry_ = "main")
            : type(type_), stage(stage_), size(size_), entry(entry_) {}
    };

    static SPtr<Shader> Create(SPtr<Device> device, void* data, Info & info);
    static void Destroy(Shader* shader);

    Info GetInfo();
    vk::ShaderModule GetNative();

    static vk::ShaderStageFlagBits StageToVk(Stage stage);

private:
    Shader();
    ~Shader();

    Info info;
    vk::ShaderModule shaderModule;

    SPtr<Device> device;

    DISALLOW_COPY_AND_ASSIGN(Shader);
};

} } }

