#ifndef DEIMOS_RENDER_H_INCLUDED
#define DEIMOS_RENDER_H_INCLUDED

#include <Phobos/Engine/Module.h>
#include <Phobos/Singleton.h>
#include <Deimos/Sprite.hpp>

namespace sample_01
{
    PH_DECLARE_SINGLETON_PTR(Render);

    class Render: public Phobos::Engine::Module
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
            deimos::Sprite spr;
    };
}

#endif