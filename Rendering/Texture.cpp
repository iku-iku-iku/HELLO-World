//
// Created by code4love on 2022/9/4.
//

#include "Texture.h"
#include "Rendering/Renderer.h"
#include "stb_image.h"
#include <iostream>
#include "GLFW/glfw3.h"

extern GLFWwindow *window;

void Texture::Bind(unsigned int slot) {
    m_Slot = slot;
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot))
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_Id))
}

void Texture::Unbind() const {
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0))
}

Texture::~Texture() {
    GLCALL(glDeleteTextures(1, &m_Id))
}

Texture::Texture(const std::string &path)  {
    stbi_set_flip_vertically_on_load(true);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

    if (m_LocalBuffer) {

        GLCALL(glGenTextures(1, &m_Id))
        GLCALL(glBindTexture(GL_TEXTURE_2D, m_Id))

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR))
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT))
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT))

        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer))
        glGenerateMipmap(GL_TEXTURE_2D);

        // 如果还启用各向异性过滤
        if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
            GLfloat anisoSetting = 0.0f;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
        }

        stbi_image_free(m_LocalBuffer);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
}

std::unique_ptr<Texture> Texture::DepthTexture() {
    auto p = std::make_unique<Texture>();

    int screenSizeX, screenSizeY;
    glfwGetFramebufferSize(window, &screenSizeX, &screenSizeY);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screenSizeX, screenSizeY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    return p;
}

Texture::Texture() {
    GLCALL(glGenTextures(1, &m_Id))
    Bind();
}
