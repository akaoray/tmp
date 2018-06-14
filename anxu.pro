TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl -lvulkan

SOURCES += main.cpp \
    xgine/graphics/core/window.cpp \
    xgine/graphics/core/context.cpp \
    xgine/app.cpp \
    xgine/graphics/core/swapchain.cpp \
    xgine/graphics/core/instance.cpp \
    xgine/graphics/core/buffer.cpp \
    xgine/graphics/core/vertexbuffer.cpp \
    xgine/graphics/core/indexbuffer.cpp \
    xgine/graphics/core/uniformbuffer.cpp \
    xgine/graphics/core/shader.cpp \
    xgine/fs/file.cpp \
    xgine/graphics/core/renderpass.cpp \
    xgine/graphics/core/framebuffers.cpp \
    xgine/graphics/core/descriptorpool.cpp \
    xgine/graphics/core/descriptorsetlayout.cpp \
    xgine/graphics/core/pipeline.cpp \
    xgine/graphics/core/commandbuffer.cpp \
    xgine/graphics/core/surface.cpp \
    xgine/graphics/core/device.cpp \
    xgine/graphics/core/descriptorset.cpp \
    xgine/graphics/core/gpulist.cpp

HEADERS += \
    xgine/graphics/core/window.h \
    xgine/base.h \
    xgine/graphics/core/context.h \
    xgine/app.h \
    xgine/graphics/core/swapchain.h \
    xgine/graphics/core/instance.h \
    xgine/graphics/core/buffer.h \
    xgine/graphics/core/vertexbuffer.h \
    xgine/graphics/core/indexbuffer.h \
    xgine/graphics/core/uniformbuffer.h \
    xgine/graphics/core/shader.h \
    xgine/fs/file.h \
    xgine/graphics/core/renderpass.h \
    xgine/graphics/core/framebuffers.h \
    xgine/graphics/core/descriptorpool.h \
    xgine/graphics/core/descriptorsetlayout.h \
    xgine/graphics/core/pipeline.h \
    xgine/graphics/core/commandbuffer.h \
    xgine/graphics/core/base.h \
    xgine/graphics/core/surface.h \
    xgine/graphics/core/device.h \
    xgine/graphics/core/descriptorset.h \
    xgine/graphics/core/gpulist.h



