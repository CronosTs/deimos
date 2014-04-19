#include "VBO.hpp"

#include <GL/glew.h>

namespace deimos
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
        { VBODrawMode::TRIANGLE, GL_TRIANGLES },
        { VBODrawMode::TRIANGLE_STRIP, GL_TRIANGLE_STRIP },
        { VBODrawMode::TRIANGLE_FAN, GL_TRIANGLE_FAN },
        { VBODrawMode::LINE, GL_LINE },
        { VBODrawMode::LINE_LOOP, GL_LINE_LOOP },
        { VBODrawMode::LINE_STRIP, GL_LINE_STRIP }
    };

    static GLTargetToVBOTarget glToVBOTarget[] =
    {
        { VBOTarget::STATIC, GL_STATIC_DRAW },
        { VBOTarget::DYNAMIC, GL_DYNAMIC_DRAW },
        { VBOTarget::STREAM, GL_STREAM_DRAW }
    };

    static GLDataTypeToVBO glDataTypeToVBO[] =
    {
        { VBODataType::SHORT, GL_SHORT },
        { VBODataType::INT, GL_INT },
        { VBODataType::FLOAT, GL_FLOAT },
        { VBODataType::DOUBLE, GL_DOUBLE }
    };

    VBO::VBO():
        m_created(false),
        m_id(0)
    {}

    VBO::VBO(const VBOData& data, int vboTarget,
        const VBOConfig& vertexConfig,
        const VBOConfig& colorConfig,
        const VBOConfig& textureConfig,
        bool freeClientData)
    {
        create();
        upload(data, vboTarget);
        configVertex(vertexConfig);
        configColor(colorConfig);
        configTexture(textureConfig);

        if (freeClientData)
            free();
    }

    VBO::~VBO()
    {
        destroy();
    }

    void VBO::create()
    {
        if (m_created)
            destroy();

        ::glGenBuffers(1, &m_id);
        m_created = true;
        ::glEnable(GL_VERTEX_ARRAY);
    }

    void VBO::destroy()
    {
        if (!m_created)
            return;

        ::glDeleteBuffers(1, &m_id);
        m_created = false;
    }

    void VBO::bind()
    {
        if (m_created)
            ::glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VBO::unbind()
    {
        //that is the proof that id is always > 0
        ::glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VBO::free()
    {
        if (!m_created)
            return;

        m_data.resize(0);
    }

    void VBO::upload(const VBOData& data, int vbotarget)
    {
        //TODO: throw exception
        if (!m_created || data.empty())
            return;

        m_data.clear();
        m_data.resize(data.size());

        //copy data
        std::copy(data.begin(), data.end(), m_data.begin());

        doUpload(vbotarget);
        
    }

    void VBO::doUpload(int vboTarget)
    {
        bind();
        ::glBufferData(GL_ARRAY_BUFFER, m_data.size(),
            static_cast<void*>(&m_data[0]),
            glToVBOTarget[vboTarget].glTarget);
    }

    void VBO::draw(int drawMode, int start, int count)
    {
        if (!m_created)
            return;

        if (count <= 0)
            count = m_data.size();

        bind();
        ::glDrawArrays(glToVBOMode[drawMode].glMode, start, count);
    }

    void VBO::configVertex(const VBOConfig& cfg)
    {
        if (!m_created)
            return;

        bind();
        ::glVertexPointer(cfg.size,
            glDataTypeToVBO[cfg.type].glType,
            cfg.stride,
            reinterpret_cast<void *>(cfg.pointer));
    }

    void VBO::configTexture(const VBOConfig& cfg)
    {
        if (!m_created)
            return;

        bind();
        ::glTexCoordPointer(cfg.size,
            glDataTypeToVBO[cfg.type].glType,
            cfg.stride,
            reinterpret_cast<void *>(cfg.pointer));
    }

    void VBO::configColor(const VBOConfig& cfg)
    {
        if (!m_created)
            return;

        bind();
        ::glColorPointer(cfg.size,
            glDataTypeToVBO[cfg.type].glType,
            cfg.stride,
            reinterpret_cast<void *>(cfg.pointer));
    }
}