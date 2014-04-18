#ifndef DEIMOS_TEXTURE_H_INCLUDED
#define DEIMOS_TEXTURE_H_INCLUDED

#include <Phobos/String.h>

namespace deimos
{
    class PH_BASE_API Texture
    {
        public:

            Texture();
            ~Texture();

            Texture(const Phobos::String_t& file);

            //only supports BMP images
            void loadFromFile(const Phobos::String_t& file);
            void bind();
            void destroy();
            unsigned int getWidth();
            unsigned int getHeight();

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