#pragma once

#include <cstdint>
#include <string>
#include <functional>

#include <GLFW/glfw3.h>

#include "src/tools/Logger.hpp"

namespace gui
{

using MouseMoveCallback = std::function<void(double, double)>;
using MouseClickCallback = std::function<void()>;

class Window
{
public:
    struct HintFactory
    {
        bool debuggable{false};

        static HintFactory createDefault()
        {
            return HintFactory
                {
                    .debuggable = false
                };
        }

        static HintFactory createDebuggable()
        {
            return HintFactory
                {
                    .debuggable = true
                };
        }
    };

public:
    Window(const std::string& windowName, const uint32_t width, const uint32_t height,
        const HintFactory& hints = HintFactory::createDefault());
    ~Window();

    void setTitle(const std::string& title);
    void enableVSync() const;
    void disableVSync() const;
    void setContextCurrent() const;
    void swap() const;
    bool shouldClose() const;

    void onMouseMove(const MouseMoveCallback& callback);
    void onMouseClick(const MouseClickCallback& callback);

    void setEventBits(const uint16_t enabledEventBits);
    void unsetEventBits(const uint16_t unsetEventBits);

    GLFWwindow* getHandle();
    uint16_t getEventBits() const;

    static bool initGlfwWindowing();
    static void terminate();
    static void pollEvents();
    static double getTime();
    static double getFPS();

private:
    void setupEventCallbacks();

    tools::Logger log_;

    GLFWwindow* windowHandle_;
    std::string windowName_;
    uint32_t width_{0};
    uint32_t height_{0};

    uint16_t enabledEventBits_{0};
    MouseMoveCallback mouseMoveCb_{nullptr};
    MouseClickCallback mouseClickCb_{nullptr};

};
} // namespace gui
