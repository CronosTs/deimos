#ifndef DEIMOS_WINDOW_H_INCLUDED
#define DEIMOS_WINDOW_H_INCLUDED

#include <Phobos/String.h>
#include <Phobos/Types.h>
#include <Phobos/BaseAPI.h>
#include <memory>

namespace deimos
{   
    class PH_BASE_API Window
    {
        public:

            ~Window();

            void open(const Phobos::String_t& title, int width, int height);
            int getWidth();
            int getHeight();
            void setClearColor(int r, int g, int b, int a);
            void clear();
            void display();

            static Window& createInstance();
            static void releaseInstance();

        private:

            void configOpenGLContext();

            Window();
            static std::shared_ptr<Window> ptr;
            
    };
}

#endif