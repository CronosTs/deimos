#include "Player.hpp"

#include <Deimos/Vector.hpp>

#include <Phobos/Shell/Utils.h>

namespace sample_01
{
    Player::Player()
    {
        m_sprite.SetTexture("player_male_base.png");
        m_sprite.LoadAnimation("player.conf");
        m_sprite.SetDelay(0.075f);
    }

    Player::~Player()
    {}

    void Player::Draw() const
    {
        m_sprite.Draw();
    }

    void Player::Movement(const Phobos::Shell::StringVector_t& args, Phobos::Shell::Context& context)
    {
        if (args[0] == "left")
        {
            m_sprite.SetCurrentAnimation("walkLeft");
            Move(Deimos::fvec2(-1, 0));
        }
        else if (args[0] == "right")
        {
            m_sprite.SetCurrentAnimation("walkRight");
            Move(Deimos::fvec2(1, 0));
        }
        else if (args[0] == "up")
        {
            m_sprite.SetCurrentAnimation("walkUp");
            Move(Deimos::fvec2(0, -1));
        }
        else if (args[0] == "down")
        {
            m_sprite.SetCurrentAnimation("walkDown");
            Move(Deimos::fvec2(0, 1));
        }
    }

    void Player::RegisterCommands(Phobos::Shell::IContext& context)
    {
        //Phobos::Shell::Command command("move", PH_CONTEXT_CMD_BIND(&Player::Move, this));
        //context.AddContextCommand(command);
    }
}