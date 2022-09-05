#ifndef __RENDERER__H_
#define __RENDERER__H_

#include <GL/glew.h>

#define GLCALL(x)   \
    GLClearError(); \
    x;              \
    GLCheckError(#x, __FILE__, __LINE__);

static const char *GetErrorMsg(GLenum err);

void GLClearError();

void GLCheckError(const char *function, const char *file, int line);

class Renderer {
public:
    void Clear();
    void Draw(const class VertexArray& va, const class  IndexBuffer&ib, const class Shader& shader) const;
};

#endif