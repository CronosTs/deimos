#ifndef DEIMOS_RENDERER_H_INCLUDED
#define DEIMOS_RENDERER_H_INCLUDED

#include "Vertex.hpp"
#include "VBO.hpp"

namespace deimos
{
    class Renderer
    {
        public:
            //vertex, primitive, offset, size
            static void Draw(const std::vector<Vertex>&, int, int, int);
            //vbo, primitive, offset, size
            static void Draw(const VBO&, int, int, int);
    };
}

#endif