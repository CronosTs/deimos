#include "Renderer.hpp"
#include "GraphicDefs.hpp"

#include <GL/glew.h>

namespace deimos
{
    void Renderer::Draw(const std::vector<Vertex>& vertex, int primitive, int offset, int size)
    {
        ::glBegin(primitive);
        for (int i = offset; i < offset + size; i++)
        {
            const fvec2& position   = vertex[i].position,
                         texture    = vertex[i].texture;
            const ubvec4& color     = vertex[i].color;

            //r, g, b, alpha
            //::glColor4ub(color.x, color.y, color.z, 0); //it's broken
            ::glTexCoord2f(texture.x, texture.y);
            ::glVertex2f(position.x, position.y);
        }
        ::glEnd();
    }
    
    void Renderer::Draw(const VBO& vbo, int primitive, int offset, int size)
    {
        vbo.bind();
        vbo.draw(primitive, offset, size);
    }
}