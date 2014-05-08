
#include <Phobos/Shell/Utils.h>
#include <Phobos/Engine/Core.h>
#include <Phobos/Memory.h>
#include <Phobos/ProcVector.h>
#include <Phobos/System/Timer.h>
#include <Phobos/Exception.h>
#include <Phobos/Log.h>

#include <exception>

#include "Render.hpp"
#include "Console.h"

void runDeimos();

int main(int argc, char** argv)
{
    runDeimos();

    return 0;
}

void runDeimos()
{
    try
    {
        Phobos::ProcVector releaseCaller;

        releaseCaller.AddProc(Phobos::Engine::Core::ReleaseInstance);
        releaseCaller.AddProc(sample_01::Render::ReleaseInstance);
        releaseCaller.AddProc(Console::ReleaseInstance);

        //precisamos de uma instancia do console.
        auto& core = Phobos::Engine::Core::CreateInstance(Console::CreateInstance(), "", 0, nullptr);
        core.AddModule(sample_01::Render::CreateInstance(), Phobos::Engine::ModulePriorities::LOWEST);

        core.StartMainLoop();

        releaseCaller.CallAll();
    }
    catch (std::exception& e)
    {
        Phobos::LogMessage(Phobos::String_t("Exception: ")
                .append(e.what()));
    }
}