#ifndef DEIMOS_RENDERABLE_H_INCLUDED
#define DEIMOS_RENDERABLE_H_INCLUDED

#include "Vector.hpp"

#include <Phobos/BaseAPI.h>

#include <memory>

namespace Deimos
{
    class Renderable;

    class PH_BASE_API  Renderable
    {
        public:

            Renderable();
            virtual ~Renderable();

            virtual void Draw() const = 0;

            void SetPosition(const fvec2&);
            void SetScale(const fvec2&);
            void Move(const fvec2&);
            void SetAngle(const float);
            

            fvec2 GetPosition() const
            {
                return m_position;
            }
            
            fvec2 GetScale() const
            {
                return m_scale;
            }
            
            float GetAngle() const
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