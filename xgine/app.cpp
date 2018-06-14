#include "app.h"

namespace xgine {

App::App()
{
    XDEBUG();
}

App::~App()
{
    XDEBUG();
}

std::shared_ptr<App> App::Create()
{
    XDEBUG();

    std::shared_ptr<App> app(new App(), App::Destroy);

    if(glfwInit() != GLFW_TRUE)
    {
        XMESSAGE("Invalid glfwInit");
        return nullptr;
    }

    if (glfwVulkanSupported() != GLFW_TRUE)
    {
        XMESSAGE("Invalid glfwVulkanSupported");
        return nullptr;
    }

    return app;
}

void App::Destroy(App* app)
{
    XDEBUG();

    assert(app != nullptr);

    delete app;

    glfwTerminate();
}

}

