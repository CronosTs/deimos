
#ifndef DEIMOS_VERTEX_H_INCLUDED
#define DEIMOS_VERTEX_H_INCLUDED

#include "Vector.hpp"

namespace Deimos
{
    //TODO: fixe msvc align problem !!!
    struct Vertex
    {
        Vertex(){}
        
        Vertex(const fvec2& pos,
               const fvec2& tex,
               const ubvec4& col):
            position(pos),
            texture(tex),
            color(col)
        {}

        fvec2 position,
              texture;
        ubvec4 color;
    };
}

#endif