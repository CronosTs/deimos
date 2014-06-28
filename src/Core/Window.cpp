#include "Window.hpp"

#include <Phobos/Log.h>
#include <Phobos/Exception.h>
#include <Phobos/Memory.h>

#include <SDL.h>
#include <memory>
#include <GL/glew.h>
#include <OpenglErrorChecker.hpp>

namespace Deimos
{

    static bool exist = false;

    Window::WindowPtr_t Window::Create(const Phobos::String_t& name)
    {
        return WindowPtr_t(PH_NEW Window(name));
    }

    Window::Window(const Phobos::String_t& name):
        WindowSDL(name)
    {}

    Window::~Window()
    {
        exist = false;
    }

    void Window::Open(const Phobos::String_t &name, const Phobos::UIntSize_t &size, unsigned int flags, void *parentWindow)
    {
        if (exist)
            PH_RAISE(Phobos::INVALID_OPERATION_EXCEPTION, "Core::Window", "Can't open window twice");

        WindowSDL::Open(name, size, flags, parentWindow);
        configOpenGLContext();
        exist = true;
    }

    void Window::configOpenGLContext()
    {
        Phobos::LogMessage("Configuring opengl context...");

        GLenum error = glewInit();
        if (error != GLEW_OK)
            PH_RAISE(Phobos::ExceptionTypes::NATIVE_API_FAILED_EXCEPTION,
                    "Render",
                    "GLEW initialization failed...");

        DEIMOS_GL_CHECK(::glOrtho(0, GetWidth(), GetHeight(), 0, 0, 500));
        DEIMOS_GL_CHECK(::glViewport(0, 0, GetWidth(), GetHeight()));
        DEIMOS_GL_CHECK(::glClearColor(0, 0, 0, 1));
        DEIMOS_GL_CHECK(::glEnable(GL_DEPTH_TEST));
        DEIMOS_GL_CHECK(::glClearDepth(1.f));
    }

    void Window::Display()
    {
        SDL_GL_SwapBuffers();
    }
}