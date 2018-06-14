#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <limits>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <algorithm>

#include <vulkan/vulkan.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#define XMESSAGE(message) std::cout<<message<<std::endl

#define DISALLOW_COPY_AND_ASSIGN(class_name) \
    class_name(const class_name& root) = delete; \
    class_name& operator=(const class_name&) = delete

#define XGINE_DEBUG

#if defined XGINE_DEBUG
#define XDEBUG() std::cout<<__PRETTY_FUNCTION__<<std::endl
#else
#define XDEBUG()
#endif

#define XGINE_NAME "xgine"
#define XGINE_VERSION 1

//template <typename T>
//using SPtr = std::shared_ptr<T>;

#define SPtr std::shared_ptr

namespace xgine {

typedef uint32_t Flags;

}
