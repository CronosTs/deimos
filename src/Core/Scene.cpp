#include "Scene.hpp"

#include <algorithm>

namespace deimos
{
    Scene::Scene()
    {}

    Scene::~Scene()
    {}

    void Scene::Draw() const
    {
        std::for_each(
            m_renderableObjects.begin(), 
            m_renderableObjects.end(),       
            [](const RenderableConstPtr_t& obj){
                fmat4 matrix = obj->GetTransformMatrix(); //TODO: matrix constructor need do this job!
                obj->Draw();
            }
        );
    }

    void Scene::AddRenderableObject(RenderablePtr_t& obj)
    {
        m_renderableObjects.push_back(obj);
    }

    void Scene::RemoveRenderableObject(RenderablePtr_t& obj)
    {
        m_renderableObjects.remove(obj);
    }
}