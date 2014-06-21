#ifndef DEIMOS_SCENE_H_INCLUDED
#define DEIMOS_SCENE_H_INCLUDED

#include "Renderable.hpp"


#include <list>
#include <memory>

namespace deimos
{
    class Scene
    {
        public:

            typedef std::shared_ptr<Renderable> RenderablePtr_t;
            typedef std::shared_ptr<const Renderable> RenderableConstPtr_t;

            Scene();
            ~Scene();

            void Draw() const;
            void AddRenderableObject(RenderablePtr_t&);
            void RemoveRenderableObject(RenderablePtr_t&);

        private:

            std::list<RenderableConstPtr_t> m_renderableObjects;
    };
}

#endif