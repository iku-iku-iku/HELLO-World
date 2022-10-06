//
// Created by code4love on 2022/9/11.
//

#include <iostream>
#include "FrameBuffer.h"
#include "Texture.h"

GLuint FrameBuffer::CurrentId = 0;

FrameBuffer::FrameBuffer() {
    GLCALL(glGenFramebuffers(1, &m_Id))
}

FrameBuffer::~FrameBuffer() {
    GLCALL(glDeleteFramebuffers(1, &m_Id))
}

void FrameBuffer::Bind() const {
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_Id))
    CurrentId = m_Id;
}

bool FrameBuffer::IsComplete() {
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void FrameBuffer::AttachDepth(const Texture &texture) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.GetId(), 0);
}

void FrameBuffer::DisableDraw() const {
    CheckBound();
    glDrawBuffer(GL_NONE);
}

void FrameBuffer::DisableRead() const {
    CheckBound();
    glReadBuffer(GL_NONE);
}

void FrameBuffer::CheckBound() const {
    if (CurrentId != m_Id) {
        std::cerr << "Framebuffer Not Bound" << std::endl;
        exit(-1);
    }
}

void FrameBuffer::ClearDepthBuffer() const {
    CheckBound();
    GLCALL(glClear(GL_DEPTH_BUFFER_BIT))
}
