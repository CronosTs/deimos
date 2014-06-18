#ifndef DEIMOS_RENDER_H_INCLUDED
#define DEIMOS_RENDER_H_INCLUDED

#include <Phobos/Engine/Module.h>
#include <Phobos/Singleton.h>
#include <Deimos/Sprite.hpp>
#include <Deimos/AnimatedSprite.hpp>

#include <Phobos/System/Timer.h>
#include <Phobos/Shell/Command.h>

namespace sample_01
{
    PH_DECLARE_SINGLETON_PTR(Render);

    class Render: public Phobos::Engine::Module
    {
        PH_DECLARE_SINGLETON_METHODS(Render);

        public:

            void OnInit() override;
            void OnStart() override;
            void OnUpdate();
            void OnRenderReady();

            //change animation
            void CmdChAnim(const Phobos::Shell::StringVector_t &args, Phobos::Shell::Context &);

            ~Render();

        protected:

            Render();

        private:

            deimos::Sprite m_sprite;
            deimos::AnimatedSprite m_animSprite;
            Phobos::Shell::Command m_left;
    };
}

#endif