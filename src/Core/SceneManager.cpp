#include "Scenemanager.hpp"

#include <algorithm>

namespace Deimos
{
    SceneManager::SceneManager()
    {}

    SceneManager::~SceneManager()
    {}

    void SceneManager::Draw() const
    {
        std::for_each(
            m_scenes.begin(), 
            m_scenes.end(), 
            [](const SceneConstPtr_t& obj){
                if (obj->IsActive())
                    obj->Draw();
            }
        );
    }

    void SceneManager::AddScene(ScenePtr_t& scene)
    {
        m_scenes.push_back(scene);
    }

    void SceneManager::AddScene(SceneConstPtr_t& scene)
    {
        m_scenes.push_back(scene);
    }

    void SceneManager::RemoveScene(ScenePtr_t& scene)
    {
        m_scenes.remove(scene);
    }

    void SceneManager::RemoveScene(SceneConstPtr_t& scene)
    {
        m_scenes.remove(scene);
    }
}