
#ifndef DEIMOS_VBO_H_INCLUDED
#define DEIMOS_VBO_H_INCLUDED

#include <Phobos/BaseAPI.h>

#include <vector>
#include <iterator>

namespace deimos
{
    enum VBODataType
    {
        SHORT,
        INT,
        FLOAT,
        DOUBLE
    };

    enum VBOType
    {
        ARRAY,
        INDEX   //not supported yet
    };

    enum VBOTarget
    {
        STATIC,
        DYNAMIC,
        STREAM
    };

    enum VBODrawMode
    {
        TRIANGLE,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        LINE,
        LINE_LOOP,
        LINE_STRIP
    };

    struct VBOConfig
    {
        VBOConfig() :
            size(0),
            type(0),
            stride(0),
            pointer(0)
        {
            //empty
        }

        VBOConfig(int _size, int _type, int _stride, int _pointer) :
            size(_size),
            type(_type),
            stride(_stride),
            pointer(_pointer)
        {}

        int size,
            type,
            stride,
            pointer;  //TODO: need a better name
    };


    class PH_BASE_API VBO
    {
        public:

            typedef std::vector<char> VBOData;

            VBO();

            VBO(const VBOData& data, int vboTarget,
                const VBOConfig& vertexConfig,
                const VBOConfig& colorConfig,
                const VBOConfig& textureConfig,
                bool freeClientData = false);

            ~VBO();

            void create();
            void destroy(); //destroy the buffer and free data from gpu side
            void bind();
            void unbind();
            void free(); //free data from client side
            void upload(const VBOData& data, int vboTarget);
            void draw(int drawMode, int start = 0, int count = -1);
            void configVertex(const VBOConfig& cfg);
            void configTexture(const VBOConfig& cfg);
            void configColor(const VBOConfig& cfg);

            template <class T>
            void upload(const std::vector<T>& vboData, int vboTarget)
            {
                m_data.resize(vboData.size() * sizeof(T));

                const char *start = reinterpret_cast<const char*>(&vboData[0]), 
                           *end   = reinterpret_cast<const char*>(&vboData[vboData.size()])
                                    + sizeof(T);

                std::copy(start,  //first adress
                          end,    //last adress. TODO: verify if this is the correct adress
                          std::back_inserter(m_data));

                doUpload(vboTarget);
            }

        protected:

            unsigned int getId()
            {
                return m_id;
            }

        private:

            void doUpload(int vbotarget);

            //non copyable
            VBO(const VBO&);

            unsigned int m_id; //id is always > 0
            bool m_created;
            VBOData m_data;

    };
}

#endif