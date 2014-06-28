#include "Renderer.hpp"
#include "GraphicDefs.hpp"
#include "OpenglErrorChecker.hpp"

#include <GL/glew.h>

namespace Deimos
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
            //::glColor4ub(color.x, color.y, color.z, color.w); //it's broken
            ::glTexCoord2f(texture.x, texture.y);
            ::glVertex2f(position.x, position.y);
        }
        DEIMOS_GL_CHECK(::glEnd());
    }
    
    void Renderer::Draw(const VBO& vbo, int primitive, int offset, int size)
    {
        vbo.Bind();
        vbo.Draw(primitive, offset, size);
    }

    void Renderer::ClearWindow()
    {
        DEIMOS_GL_CHECK(::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void Renderer::SetClearColor(Phobos::UInt8_t red, Phobos::UInt8_t green, Phobos::UInt8_t blue, Phobos::UInt8_t alpha)
    {
        float r = static_cast<float>(red),
              g = static_cast<float>(green),
              b = static_cast<float>(blue),
              a = static_cast<float>(alpha);

        DEIMOS_GL_CHECK(::glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f));
    }
}