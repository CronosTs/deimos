#include "Window.hpp"

#include <Phobos/Log.h>
#include <Phobos/Exception.h>

#include <SDL.h>
#include <memory>
#include <GL/glew.h>
#include <OpenglErrorChecker.hpp>

namespace deimos
{
    std::shared_ptr<Window> Window::ptr;

    Window& Window::createInstance()
    {
        if (ptr == nullptr)
            ptr.reset(new Window());

        return *ptr;
    }

    void Window::releaseInstance()
    {
        ptr.reset();
    }
    
    void Window::open(const Phobos::String_t& title, int width, int height)
    {
        SDL_Init(SDL_INIT_VIDEO);

        unsigned int flags = SDL_OPENGL; //| SDL_NOFRAME;

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        
        SDL_SetVideoMode(width, height, 32, flags);

        SDL_WM_SetCaption(title.c_str(), nullptr);

        configOpenGLContext();
    }

    void Window::configOpenGLContext()
    {
        Phobos::LogMessage("Configuring opengl context...");

        GLenum error = glewInit();
        if (error != GLEW_OK)
            PH_RAISE(Phobos::ExceptionTypes::NATIVE_API_FAILED_EXCEPTION,
                    "Render",
                    "GLEW initialization failed...");

        DEIMOS_GL_CHECK(::glOrtho(0, getWidth(), getHeight(), 0, 0, 500));
        DEIMOS_GL_CHECK(::glViewport(0, 0, getWidth(), getHeight()));
        DEIMOS_GL_CHECK(::glClearColor(0, 0, 0, 1));
        DEIMOS_GL_CHECK(::glEnable(GL_DEPTH_TEST));
        DEIMOS_GL_CHECK(::glClearDepth(1.f));
    }

    int Window::getWidth()
    {
        return SDL_GetVideoSurface()->w;
    }

    int Window::getHeight()
    {
        return SDL_GetVideoSurface()->h;
    }

    void Window::setClearColor(int r, int g, int b, int a)
    {
        DEIMOS_GL_CHECK(::glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f));
    }

    void Window::clear()
    {
        DEIMOS_GL_CHECK(::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void Window::display()
    {
        SDL_GL_SwapBuffers();
    }

    Window::~Window()
    {
        SDL_Quit();
    }

    Window::Window()
    {}
}