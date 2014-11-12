#ifndef DEIMOS_OPENGL_ERROR_CHECKER_H_INCLUDED
#define DEIMOS_OPENGL_ERROR_CHECKER_H_INCLUDED

#include <Phobos/Log.h>
#include <GL/glew.h>
#include <sstream>

#ifdef PH_DEBUG

#define DEIMOS_GL_CHECK(x)                                          \
    do{                                                             \
        x;                                                          \
        GLenum error = glGetError();                                \
        if (error != GL_NO_ERROR)                                   \
        {                                                           \
            std::stringstream ss;                                   \
            ss << "OpenglError: " << (char*)gluErrorString(error)   \
               << " [" << __FILE__ << ":" << __LINE__<<"]";         \
            Phobos::LogMessage(ss.str());                           \
        }                                                           \
    }while (0)
#else
    #define DEIMOS_GL_CHECK(x) x;
#endif

#endif