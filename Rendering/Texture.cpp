//
// Created by code4love on 2022/9/4.
//

#include "Texture.h"
#include "Rendering/Renderer.h"
#include "stb_image.h"
#include <iostream>

void Texture::Bind(unsigned int slot) const {
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot))
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_Id))
}

void Texture::Unbind() const {
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0))
}

Texture::~Texture() {
    GLCALL(glDeleteTextures(1, &m_Id))
}

Texture::Texture(const std::string &path) : m_Id(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {
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
