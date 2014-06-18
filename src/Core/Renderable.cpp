#include "Renderable.hpp"

#include <cmath>

namespace deimos
{
    Renderable::Renderable():
        m_scale(1, 1),
        m_angle(0)
    {}

    Renderable::~Renderable()
    {}

    void Renderable::SetPosition(const fvec2& position)
    {
        m_position = position;
    }

    void Renderable::SetScale(const fvec2& scale)
    {
        m_scale = scale;
    }

    void Renderable::SetAngle(float angle)
    {
        m_angle = angle;
    }

    fmat4 Renderable::GetTransformMatrix()
    {
        fmat4 matrix;

        float x = m_scale.x, //sale
              y = m_scale.y,
              s = sin(m_angle),
              c = cos(m_angle);

        //rotation
        x = x*c - y*s;
        y = x*s + y*c;

        //translation
        x += m_position.x;
        y += m_position.y;

        matrix.At(0, 0) = x;
        matrix.At(1, 1) = y;

        return matrix;
    }
}