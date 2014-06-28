#ifndef DEIMOS_TEXTURE_H_INCLUDED
#define DEIMOS_TEXTURE_H_INCLUDED

#include <Phobos/String.h>

namespace Deimos
{
    class PH_BASE_API Texture
    {
        public:

            Texture();
            ~Texture();

            Texture(const Phobos::String_t& file);

            void LoadFromFile(const Phobos::String_t& file);
            void Bind();
            void Destroy();
            unsigned int GetWidth();
            unsigned int GetHeight();

        private:

            //non copyable
            Texture(const Texture&);

            bool m_created;
            unsigned int m_id,
                         m_width,
                         m_height;
    };
}

#endif