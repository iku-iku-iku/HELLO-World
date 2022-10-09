//
// Created by code4love on 2022/9/11.
//

#ifndef HELLO_FRAMEBUFFER_H
#define HELLO_FRAMEBUFFER_H

#include <GL/glew.h>
#include "Core/Log.h"

class FrameBuffer {
public:
    FrameBuffer();

    ~FrameBuffer();

    void Bind() const;

    static void UnBind() { UseDefault(); }

    static void UseDefault() {
        CurrentId = 0;
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0))
    }

    static bool IsComplete();

    static void AttachDepth(const class Texture &texture);

    GLuint GetId() const { return m_Id; }

    void DisableDraw() const;

    void DisableRead() const;

    void ClearDepthBuffer() const;

    void CheckBound() const;


private:
    GLuint m_Id;

    static GLuint CurrentId;
};

#endif //HELLO_FRAMEBUFFER_H
