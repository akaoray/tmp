#pragma once

#include "base.h"

namespace xgine {

class App
{
public:
    static std::shared_ptr<App> Create();
    static void Destroy(App* app);

private:
    App();
    ~App();

    DISALLOW_COPY_AND_ASSIGN(App);
};

}
