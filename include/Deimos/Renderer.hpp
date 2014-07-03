#ifndef DEIMOS_RENDERER_H_INCLUDED
#define DEIMOS_RENDERER_H_INCLUDED

#include <Phobos/Types.h>
#include <Phobos/BaseAPI.h>

#include "Vertex.hpp"
#include "VBO.hpp"
#include "Matrix.hpp"

namespace Deimos
{
    class PH_BASE_API Renderer
    {
        public:

            //vertex, primitive, offset, size
            static void Draw(const std::vector<Vertex>&, int, int, int);
            //vbo, primitive, offset, size
            static void Draw(const VBO&, int, int, int);
            
            static void ClearWindow();
            static void SetClearColor(Phobos::UInt8_t red, Phobos::UInt8_t green, Phobos::UInt8_t blue, Phobos::UInt8_t alpha);
            static void SaveCurrentTransform();
            static void RestorePreviousTransform();
            static void SetTransform(fmat4&);
            static void AplyTransform(fmat4&);
    };
}

#endif