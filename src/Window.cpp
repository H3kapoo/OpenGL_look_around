#include "Window.hpp"

#include <cstdint>

#include <GLFW/glfw3.h>

#include "src/common/WindowCommon.hpp"

namespace gui
{
using namespace tools;

Window::Window(const std::string& windowName, const uint32_t width, const uint32_t height, const HintFactory& hints)
    : log_{"Window(" + windowName +")"}
    , windowName_(windowName)
    , width_(width)
    , height_(height)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (hints.debuggable)
    {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    }

    windowHandle_ = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (!windowHandle_)
    {
        log_.error("Failed to create!");
        glfwTerminate();
        return;
    }

    log_.info("Created!");

    glViewport(0, 0, width_, height_);
    disableVSync();
    setupEventCallbacks();
}

Window::~Window()
{
    log_.info("Destroying window..");
    glfwDestroyWindow(windowHandle_);
}

void Window::setTitle(const std::string& title)
{
    glfwSetWindowTitle(windowHandle_, title.c_str());
}

void Window::setEventBits(const uint16_t setEventBits)
{
    enabledEventBits_ |= setEventBits;
}

void Window::unsetEventBits(const uint16_t unsetEventBits)
{
    enabledEventBits_ &= ~unsetEventBits;
}

void Window::setupEventCallbacks()
{
    glfwSetWindowUserPointer(windowHandle_, this);

    glfwSetCursorPosCallback(windowHandle_, [](GLFWwindow* win, double xPos, double yPos){
        Window* w =  static_cast<Window*>(glfwGetWindowUserPointer(win));
        if (w->mouseMoveCb_ && (w->enabledEventBits_ & common::WindowInputBit::MOUSE_MOVE))
        {
            w->mouseMoveCb_(xPos, yPos);
        };
    });

    glfwSetMouseButtonCallback(windowHandle_, [](GLFWwindow* win, int button, int action, int mods){
        (void)button;
        (void)mods;

        if (action != GLFW_RELEASE)
        {
            return;
        }

        Window* w =  static_cast<Window*>(glfwGetWindowUserPointer(win));
        if (w->mouseClickCb_ && (w->enabledEventBits_ & common::WindowInputBit::MOUSE_CLICK))
        {
            w->mouseClickCb_();
        };
    });
}

void Window::onMouseMove(const MouseMoveCallback& callback)
{
    mouseMoveCb_ = callback;
}

void Window::onMouseClick(const MouseClickCallback& callback)
{
    mouseClickCb_ = callback;
}

void Window::enableVSync() const
{
    glfwSwapInterval(1);
}

void Window::disableVSync() const
{
    glfwSwapInterval(0);
}

void Window::setContextCurrent() const
{
    glfwMakeContextCurrent(windowHandle_);
}

void Window::swap() const
{
    glfwSwapBuffers(windowHandle_);
}

GLFWwindow* Window::getHandle()
{
    return windowHandle_;
}

uint16_t Window::getEventBits() const
{
    return enabledEventBits_;
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(windowHandle_);
}

bool Window::initGlfwWindowing()
{
    return glfwInit();
}

void Window::terminate()
{
    glfwTerminate();
}

void Window::pollEvents()
{
    glfwPollEvents();
}

double Window::getTime()
{
    return glfwGetTime();
}

double Window::getFPS()
{
    return glfwGetTime();
}
} // namespace gui
