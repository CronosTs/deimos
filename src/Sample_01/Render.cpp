#include "Render.hpp"
#include "Console.h"

#include <Deimos/Window.hpp>
#include <Deimos/OpenglErrorChecker.hpp>
#include <Deimos/Renderer.hpp>

#include <Phobos/Log.h>
#include <Phobos/Engine/Core.h>
#include <Phobos/Singleton.h>
#include <Phobos/Register/Manager.h>
#include <Phobos/Register/Hive.h>
#include <Phobos/Register/Table.h>

#include <GL/glew.h>

#include <functional>

#include <fstream>



namespace sample_01
{
    PH_DEFINE_DEFAULT_SINGLETON(Render);

    Render::Render():
        Phobos::Engine::Module("Render"),
        m_left("left")
    {
        auto &console = Console::CreateInstance();
        console.AddContextCommand(m_left);
    }

    Render::~Render()
    {}

    void Render::OnInit()
    {
        Phobos::LogMessage("[Render::OnInit] Starting");
        Phobos::LogMessage("[Render::OnInit] Creating window");

        m_window = Deimos::Window::Create("MyWindow");
        m_window->Open("Sample01", Phobos::UIntSize_t(800, 600), Phobos::System::Window::WND_OPENGL_CONTEXT);
        Deimos::Renderer::SetClearColor(255, 255, 255, 0);
        
        Phobos::LogMessage("[Render::OnInit] Ready.");
    }

    void Render::OnStart()
    {
        Phobos::LogMessage("[Render::OnStart] Initing...");
        Phobos::LogMessage("[Render::OnStart] Load Resources...");

        m_sprite.SetTexture("player_male_base.png");
        m_sprite.SetRect(Deimos::Sprite::FRect(21, 6, 20, 54));
        m_animSprite.SetTexture(m_sprite.GetTexture());

        //load animations
        Phobos::LogMessage("[Render::OnStart] Loading assets.");
        m_animSprite.LoadAnimation("player.conf");
        m_animSprite.SetCurrentAnimation("WalkDown");
        m_animSprite.SetDelay(0.075f);

        Phobos::LogMessage("[Render::OnStart] Done.");

        glMatrixMode(GL_MODELVIEW);//TODO: remove this
    }

    void Render::OnUpdate()
    {
        Deimos::Renderer::ClearWindow();

        /*texture.bind();
        glBegin(GL_TRIANGLES);
            glTexCoord2f(0.f, 0.f); 
            glVertex2f(0.f, 0.f);
            
            glTexCoord2f(0.f, 1.f); 
            glVertex2f(0.f, 480);
            
            glTexCoord2f(1.f, 0.f);
            glVertex2f(288, 0);
            
            glTexCoord2f(0.f, 1.f); 
            glVertex2f(0.f, 480);
            
            glTexCoord2f(1.f, 1.f);
            glVertex2f(288, 480);
            
            glTexCoord2f(1.f, 0.f); 
            glVertex2f(288, 0.f);
        DEIMOS_GL_CHECK(glEnd());*/

        /*glPushMatrix();
        glScalef(0.5f, 0.5f, 1);
        m_sprite.draw();
        glPopMatrix();*/

        m_animSprite.Update();
        m_animSprite.Draw();

        m_window->SwapBuffers();
    }

    void Render::CmdChAnim(const Phobos::Shell::StringVector_t &args, Phobos::Shell::Context &context)
    {
        m_animSprite.SetCurrentAnimation(args[0]);
    }
}