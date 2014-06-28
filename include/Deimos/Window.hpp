#ifndef DEIMOS_WINDOW_H_INCLUDED
#define DEIMOS_WINDOW_H_INCLUDED

#include <Phobos/String.h>
#include <Phobos/Types.h>
#include <Phobos/BaseAPI.h>
#include <Phobos/System/SDL/WindowSDL.h>
#include <memory>

namespace Deimos
{
    class PH_BASE_API Window: public Phobos::System::WindowSDL
    {
        public:

            typedef std::shared_ptr<Window> WindowPtr_t;
            typedef std::weak_ptr<Window> WindowWeakPtr_t;

            static WindowPtr_t Create(const Phobos::String_t& name);

            virtual void Open(const Phobos::String_t &name, const Phobos::UIntSize_t &size, unsigned int flags, void *parentWindow = NULL) override;

            //swap opengl buffers
            void Display();

            virtual ~Window();

        private:
       
            Window(const Phobos::String_t&);
            void Window::configOpenGLContext();
    };
}

#endif