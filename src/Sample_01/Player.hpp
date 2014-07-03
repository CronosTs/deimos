#ifndef DEIMOS_PLAYER_H_INCLUDED
#define DEIMOS_PLAYER_H_INCLUDED


#include <Deimos/AnimatedSprite.hpp>
#include <Deimos/Renderable.hpp>

#include <Phobos/Shell/CommandFwd.h>
#include <Phobos/Shell/Context.h>
#include <Phobos/Shell/IContext.h>

namespace sample_01
{
    class Player: public Deimos::Renderable
    {
        public:

            Player();
            ~Player();

            void Draw() const;
            void Movement(const Phobos::Shell::StringVector_t&, Phobos::Shell::Context&);
            void RegisterCommands(Phobos::Shell::IContext&);

        private:

            Deimos::AnimatedSprite m_sprite;
    };
}

#endif