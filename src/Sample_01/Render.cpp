#include "Render.hpp"

#include <Phobos/Log.h>
#include <Phobos/Engine/Core.h>
#include <Phobos/Singleton.h>
#include <GL/glew.h>
#include <Deimos/Window.hpp>

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
        
        texture.loadFromFile("player_male_base.png");

        Phobos::LogMessage("[Render::OnStart] Done.");
    }

    void Render::OnUpdate()
    {
        auto& wnd = deimos::Window::createInstance();
        wnd.clear();
        //spr.draw();

        glBegin(GL_TRIANGLES);
            texture.bind();
            glTexCoord2f(0.f, 0.f); 
            glVertex2f(0.f, 0.f);
            
            glTexCoord2f(0.f, texture.getHeight()); 
            glVertex2f(0.f, texture.getHeight());
            
            glTexCoord2f(texture.getWidth(), texture.getHeight()); 
            glVertex2f(texture.getWidth(), texture.getHeight());
            
            glTexCoord2f(0.f, texture.getHeight()); 
            glVertex2f(0.f, texture.getHeight());
            
            glTexCoord2f(texture.getWidth(), texture.getHeight()); 
            glVertex2f(texture.getWidth(), texture.getHeight());
            
            glTexCoord2f(texture.getWidth(), 0.f); 
            glVertex2f(texture.getWidth(), 0.f);
        glEnd();

        wnd.display();
    }
}