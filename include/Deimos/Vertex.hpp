
#ifndef DEIMOS_VERTEX_H_INCLUDED
#define DEIMOS_VERTEX_H_INCLUDED

#include "Vector.hpp"

namespace deimos
{
    //TODO: fixe msvb align problem !!!
    struct Vertex
    {
        Vertex(){}
        
        Vertex(const fvec2& pos,
               const fvec2& tex,
               const ivec3& col):
            position(pos),
            texture(tex),
            color(col)
        {}

        fvec2 position,
              texture;
        ivec3 color;
    };
}

#endif