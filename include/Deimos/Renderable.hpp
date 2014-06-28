#ifndef DEIMOS_RENDERABLE_H_INCLUDED
#define DEIMOS_RENDERABLE_H_INCLUDED

#include "Vector.hpp"
#include "Matrix.hpp"

#include <Phobos/BaseAPI.h>

#include <memory>

namespace Deimos
{
    class Renderable;

    class PH_BASE_API  Renderable
    {
        public:

            Renderable();
            ~Renderable();

            virtual void Draw() const = 0;

            void SetPosition(const fvec2&);
            void SetScale(const fvec2&);
            void SetAngle(const float);
            fmat4 GetTransformMatrix() const;

            fvec2 GetPosition()
            {
                return m_position;
            }
            
            fvec2 GetScale()
            {
                return m_scale;
            }
            
            float GetAngle()
            {
                return m_angle;
            }

        private:

            fvec2 m_position,
                  m_scale;

            float m_angle;
    };
}

#endif