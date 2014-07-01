#ifndef DEIMOS_SCENE_MANAGER_H_INCLUDED
#define DEIMOS_SCENE_MANAGER_H_INCLUDED

#include "Scene.hpp"

#include <Phobos/BaseAPI.h>
#include <list>
#include <memory>

namespace Deimos
{
    class PH_BASE_API SceneManager
    {
        public:

            typedef std::shared_ptr<Scene> ScenePtr_t;
            typedef std::shared_ptr<const Scene> SceneConstPtr_t;
            typedef std::weak_ptr<Scene> SceneWeakPtr_t;

            SceneManager();
            ~SceneManager();

            void Draw() const;

            void AddScene(ScenePtr_t&);
            void AddScene(SceneConstPtr_t&);
            void RemoveScene(ScenePtr_t&);
            void RemoveScene(SceneConstPtr_t&);

        private:

            std::list<SceneConstPtr_t> m_scenes;
    };
}

#endif