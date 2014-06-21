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

    fmat4 Renderable::GetTransformMatrix() const
    {
        fmat4 matrix;

        for (int i = 0; i < 4; i++)
            matrix[i][i] = 1;

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

        matrix[0][3] = x;
        matrix[1][3] = y;

        return matrix;
    }
}