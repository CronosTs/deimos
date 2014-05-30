#ifndef DEIMOS_SPRITE_H_INCLUDED
#define DEIMOS_SPRITE_H_INCLUDED

#include <Phobos/System/Timer.h>
#include <Phobos/Types.h>
#include <Phobos/String.h>

#include <memory>

#include "Texture.hpp"
#include "Mesh.hpp"
#include "Vertex.hpp"

namespace deimos
{
    class PH_BASE_API Sprite
    {
        public:

            struct Quads
            {
               /* t1          t2
                    +--------+
                    |        |
                    |        |
                    |        |
                    +--------+
                  t3          t4
               */


                Vertex t1, t2, t3, t4;
            };

            typedef Phobos::Rect_s<Phobos::Float32_t> FRect;
            typedef std::shared_ptr<Texture> TexturePtr_t;
            

            Sprite();
            ~Sprite();

            inline void setVisible(bool);
            void draw();
            void setRect(const FRect&);
            void setTexture(TexturePtr_t&);
            void setTexture(const Phobos::String_t&);
            TexturePtr_t getTexture();

        private:

            bool m_visible;
            FRect m_rect;
            std::shared_ptr<Texture> m_texture;
            Mesh m_mesh;
    };
}

#endif