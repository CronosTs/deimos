#include "Scene.hpp"
#include "Matrix.hpp"

#include <algorithm>

#include <GL/glew.h>

namespace Deimos
{
    Scene::Scene():
        m_active(false)
    {}

    Scene::~Scene()
    {}

    void Scene::SetActive(bool active)
    {
        m_active = active;
    }

    void Scene::Draw() const
    {
        std::for_each(
            m_renderableObjects.begin(), 
            m_renderableObjects.end(),       
            [](const RenderableConstPtr_t& obj){

                fmat4 matrix = TranslationMatrix(obj->GetPosition().x, obj->GetPosition().y, 0.f)
                             * ZRotationMatrix(obj->GetAngle())
                             * ScalingMatrix(obj->GetScale().x, obj->GetScale().y, 1.f);

                //glMultMatrixf(&matrix[0][0]);

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