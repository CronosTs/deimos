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
        return TranslationMatrix(m_position.x, m_position.y, 0.f) * 
               ZRotationMatrix(m_angle) * 
               ScalingMatrix(m_scale.x, m_scale.y, 1.f);
    }
}