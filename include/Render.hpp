#ifndef DEIMOS_RENDER_H_INCLUDED
#define DEIMOS_RENDER_H_INCLUDED

#include <Phobos/Engine/Module.h>
#include <Phobos/Singleton.h>

#include "Window.hpp"
#include "VBO.hpp"

namespace deimos
{
    PH_DECLARE_SINGLETON_PTR(Render);

    class PH_BASE_API Render: public Phobos::Engine::Module
    {
        PH_DECLARE_SINGLETON_METHODS(Render);

        public:

            void OnBoot();
            void OnUpdate();
            void OnRenderReady();

            ~Render();

        protected:

            Render();

        private:

            bool renderReady;
    };
}

#endif