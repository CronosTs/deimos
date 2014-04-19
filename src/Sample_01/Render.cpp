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
        Phobos::Engine::Module("Render"),
        renderReady(false)
    {}

    Render::~Render()
    {
        deimos::Window::releaseInstance();
    }

    void Render::OnBoot()
    {
        Phobos::LogMessage("[Render::OnBoot] Starting");
        Phobos::LogMessage("[Render::OnBoot] Creating window");

        deimos::Window::createInstance().open("MyWindow", 800, 600);
        deimos::Window::createInstance().clear();
        
        Phobos::LogMessage("[Render::OnBoot] Ready.");
        Phobos::Engine::Core::GetInstance().OnEvent(Phobos::Engine::Core::Events::RENDER_READY);
    }

    void Render::OnRenderReady()
    {
        renderReady = true;

        spr.setTexture("player_male_base.png");
        spr.setVisible(true);
    }

    void Render::OnUpdate()
    {
        if (!renderReady)
            return;

        auto& wnd = deimos::Window::createInstance();
        wnd.clear();
        spr.draw();

        /*glBegin(GL_TRIANGLES);
            
            glColor3f(1, 0, 0); glVertex2f(400, 0);
            glColor3f(1, 0, 0); glVertex2f(0, 600);
            glColor3f(1, 0, 0); glVertex2f(800, 600);
            
            glColor3f(0, 1, 0); glVertex2f(400, 100);
            glColor3f(0, 1, 0); glVertex2f(100, 500);
            glColor3f(0, 1, 0); glVertex2f(700, 500);

        glEnd();*/

        wnd.display();
    }
}