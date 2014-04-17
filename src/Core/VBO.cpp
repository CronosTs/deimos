#include "VBO.hpp"

struct Vert
{
    float x, y, tx, ty;
    int r, g, b;
};

deimos::VBO<Vert> myVBO;

/*
#include <GL/glew.h>

namespace deimos
{
    struct GLModeToVBO
    {
        int glMode;
        int vboMode;
    };

    static GLModeToVBO glToVBOMode[] =
    {
        { VBODrawMode::TRIANGLE,        GL_TRIANGLES},
        { VBODrawMode::TRIANGLE_STRIP,  GL_TRIANGLE_STRIP },
        { VBODrawMode::TRIANGLE_FAN,    GL_TRIANGLE_FAN },
        { VBODrawMode::LINE,            GL_LINE },
        { VBODrawMode::LINE_LOOP,       GL_LINE_LOOP },
        { VBODrawMode::LINE_STRIP,      GL_LINE_STRIP }
    };

    struct GLTargetToVBOTarget
    {
        int glTarget;
        int vbotarget;
    };

    static GLTargetToVBOTarget glToVBOTarget[] = 
    {
        {VBOTarget::STATIC,   GL_STATIC_DRAW},
        {VBOTarget::DYNAMIC,  GL_DYNAMIC_DRAW},
        {VBOTarget::STREAM,   GL_STREAM_DRAW}
    };


    VBO::VBO():
        id(0),
        created(false)
    {}

    VBO::~VBO()
    {
        erase();
    }

    void VBO::create()
    {
        if (created)
            erase();

        glGenBuffers(1, &id); //TODO: check opengl errors
        created = true;
    }

    void VBO::erase()
    {
        if (!created)
            return;

        glDeleteBuffers(1, &id);
        id = 0;
        created = false;   
    }

    void VBO::free()
    {
        data.resize(0);
    }

    void VBO::bind()
    {
        //TODO: throw exception
        if (!created)
            return;

        //TODO: use enums from VBO's class
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VBO::upload(const VBOData& _data, int count, int vbotarget)
    {
        //TODO: throw exception
        if (!created || _data.empty())
            return;

        vertexCount = count;
        data.clear();
        data.resize(_data.size());

        //copy data
        std::copy(_data.begin(), _data.end(), data.begin());

        bind();
        
        glBufferData(GL_ARRAY_BUFFER, data.size(), 
                     static_cast<void*>(&data[0]), 
                     glToVBOTarget[vbotarget].glTarget);
    }

    void VBO::setId(unsigned int _id)
    {
        id = _id;
    }

    unsigned int VBO::getId()
    {
        return id;
    }

    void VBO::draw(int drawMode, int start, int count)
    {
        bind();

        if (count == -1)
            count = vertexCount;

        glDrawArrays(glToVBOMode[drawMode].glMode, start, count);
    }
}

*/