
#include <Phobos/Shell/Utils.h>
#include <Phobos/Engine/Core.h>
#include <Phobos/Engine/EventManagerModule.h>
#include <Phobos/Memory.h>
#include <Phobos/ProcVector.h>
#include <Phobos/System/Timer.h>

#include "Render.hpp"

void runDeimos();

int main(int argc, char** argv)
{
    runDeimos();

    return 0;
}

void runDeimos()
{
    Phobos::ProcVector releaseCaller;

    releaseCaller.AddProc(Phobos::Engine::Core::ReleaseInstance);
    releaseCaller.AddProc(Phobos::Engine::EventManagerModule::ReleaseInstance);
    releaseCaller.AddProc(sample_01::Render::ReleaseInstance);

    auto& core = Phobos::Engine::Core::CreateInstance();
    core.AddModule(Phobos::Engine::EventManagerModule::CreateInstance());
    core.AddModule(sample_01::Render::CreateInstance(), Phobos::Engine::ModulePriorities::LOWEST);

    core.LaunchBootModule("", 0, nullptr);

    core.MainLoop();

    releaseCaller.CallAll();
}