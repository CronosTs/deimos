#include "Render.hpp"

#include <Phobos/Log.h>
#include <Phobos/Engine/Core.h>
#include <Phobos/Singleton.h>
#include <GL/glew.h>
#include <Deimos/Window.hpp>
#include <Deimos/OpenglErrorChecker.hpp>


namespace sample_01
{
    PH_DEFINE_DEFAULT_SINGLETON(Render);

    Render::Render():
        Phobos::Engine::Module("Render")
    {}

    Render::~Render()
    {
        deimos::Window::releaseInstance();
    }

    void Render::OnInit()
    {
        Phobos::LogMessage("[Render::OnInit] Starting");
        Phobos::LogMessage("[Render::OnInit] Creating window");

        deimos::Window::createInstance().open("MyWindow", 800, 600);
        deimos::Window::createInstance().clear();
        
        Phobos::LogMessage("[Render::OnInit] Ready.");
        
    }

    void Render::OnStart()
    {
        Phobos::LogMessage("[Render::OnStart] Initing...");
        Phobos::LogMessage("[Render::OnStart] Load Resources...");

        m_sprite.setTexture("player_male_base.png");

        Phobos::LogMessage("[Render::OnStart] Done.");
    }

    void Render::OnUpdate()
    {
        auto& wnd = deimos::Window::createInstance();

        wnd.clear();

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

        m_sprite.draw();

        wnd.display();
    }
}