
#ifndef DEIMOS_VBO_H_INCLUDED
#define DEIMOS_VBO_H_INCLUDED

#include <vector>
#include <GL/glew.h>

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

    namespace
    {
        struct GLTargetToVBOTarget
        {
            int glTarget;
            int vbotarget;
        };

        struct GLModeToVBO
        {
            int glMode;
            int vboMode;
        };

        struct GLDataTypeToVBO
        {
            int glType,
                vboType;
        };

        static GLModeToVBO glToVBOMode[] =
        {
            { VBODrawMode::TRIANGLE,        GL_TRIANGLES },
            { VBODrawMode::TRIANGLE_STRIP,  GL_TRIANGLE_STRIP },
            { VBODrawMode::TRIANGLE_FAN,    GL_TRIANGLE_FAN },
            { VBODrawMode::LINE,            GL_LINE },
            { VBODrawMode::LINE_LOOP,       GL_LINE_LOOP },
            { VBODrawMode::LINE_STRIP,      GL_LINE_STRIP }
        };

        static GLTargetToVBOTarget glToVBOTarget[] =
        {
            { VBOTarget::STATIC,  GL_STATIC_DRAW },
            { VBOTarget::DYNAMIC, GL_DYNAMIC_DRAW },
            { VBOTarget::STREAM,  GL_STREAM_DRAW }
        };

        static GLDataTypeToVBO glDataTypeToVBO[] =
        {
            { VBODataType::SHORT,   GL_SHORT },
            { VBODataType::INT,     GL_INT },
            { VBODataType::FLOAT,   GL_FLOAT },
            { VBODataType::DOUBLE,  GL_DOUBLE }
        };
    }

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


    template<class T>
    class VBO
    {
        public:

            typedef std::vector<T> VBOData;

            VBO() :
                m_created(false),
                m_id(0)
            {}

            VBO(const VBOData& data, int vboTarget,
                const VBOConfig& vertexConfig,
                const VBOConfig& colorConfig,
                const VBOConfig& textureConfig,
                bool freeClientData = false)
            {
                create();
                upload(data, vboTarget);
                configVertex(vertexConfig);
                configColor(colorConfig);
                configTexture(textureConfig);

                if (freeClientData)
                    free();
            }

            ~VBO()
            {
                destroy();
            }

            void create()
            {
                if (m_created)
                    destroy();

                ::glGenBuffers(1, &m_id);
                m_created = true;
                ::glEnable(GL_VERTEX_ARRAY);
            }

            //destroy the vuffer and free data from gpu side
            void destroy()
            {
                if (!m_created)
                    return;

                ::glDeleteBuffers(1, &m_id);
                m_created = false;
            }

            void bind()
            {
                if (m_created)
                    ::glBindBuffer(GL_ARRAY_BUFFER, m_id);
            }

            void unbind()
            {
                //that is the proof that id is always > 0
                ::glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            //free data from client side
            void free()
            {
                if (!m_created)
                    return;

                m_data.resize(0);
            }

            void upload(const VBOData& data, int vbotarget)
            {
                //TODO: throw exception
                if (!m_created || data.empty())
                    return;

                m_data.clear();
                m_data.resize(data.size());

                //copy data
                std::copy(data.begin(), data.end(), m_data.begin());

                bind();
                ::glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T),
                    static_cast<void*>(&data[0]),
                    glToVBOTarget[vbotarget].glTarget);
            }

            void draw(int drawMode, int start=0, int count=m_data.size())
            {
                if (!m_created)
                    return;

                bind();
                ::glDrawArrays(glToVBOMode[drawMode].glMode, start, count);
            }

            void configVertex(const VBOConfig& cfg)
            {
                if (!m_created)
                    return;

                bind();
                ::glVertexPointer(cfg.size, 
                                  glDataTypeToVBO[cfg.type].glType,
                                  cfg.stride, 
                                  reinterpret_cast<void *>(cfg.pointer));
            }

            void configTexture(const VBOConfig& cfg)
            {
                if (!m_created)
                    return;

                bind();
                ::glTexCoordPointer(cfg.size,
                                    glDataTypeToVBO[cfg.type].glType,
                                    cfg.stride,
                                    reinterpret_cast<void *>(cfg.pointer));
            }

            void configColor(const VBOConfig& cfg)
            {
                if (!m_created)
                    return;

                bind();
                ::glColorPointer(cfg.size,
                                 glDataTypeToVBO[cfg.type].glType,
                                 cfg.stride,
                                 reinterpret_cast<void *>(cfg.pointer));
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
            bool m_created;
            VBOData m_data;

    };
}

#endif