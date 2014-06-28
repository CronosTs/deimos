
#ifndef DEIMOS_VBO_H_INCLUDED
#define DEIMOS_VBO_H_INCLUDED

#include <Phobos/BaseAPI.h>

#include <vector>
#include <iterator>

namespace Deimos
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

            void Create();
            void Destroy(); //destroy the bufferr
            void Bind() const;
            void Unbind() const;
            void Upload(const VBOData& data, int vboTarget);
            void Draw(int drawMode, int start = 0, int count = 0) const;
            void ConfigVertex(const VBOConfig& cfg) const;
            void ConfigTexture(const VBOConfig& cfg) const;
            void ConfigColor(const VBOConfig& cfg) const;

            bool HasCreated() const
            {
                return m_created;
            }

            template <class T>
            void Upload(const std::vector<T>& vboData, int vboTarget)
            {
                m_size = vboData.size();

                if (m_size <= 0)
                    return; //TODO: throw exception

                VBOData data;
                data.reserve(vboData.size() * sizeof(T));

                const char *start = reinterpret_cast<const char*>(&vboData[0]), 
                           *end   = reinterpret_cast<const char*>(&vboData[vboData.size()-1])
                                    + sizeof(T);

                std::copy(start,  //first adress
                          end,    //last adress. TODO: verify if this is the correct adress
                          std::back_inserter(data));

                Upload(data, vboTarget);
            }

        protected:

            unsigned int getId()
            {
                return m_id;
            }

        private:

            //non copyable
            VBO(const VBO&);

            unsigned int m_id; //id is always > 0
            unsigned int m_size;
            bool m_created;
    };
}

#endif