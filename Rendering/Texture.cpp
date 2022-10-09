//
// Created by code4love on 2022/9/4.
//

#include "Texture.h"
#include "Core/Log.h"
#include "Rendering/Renderer.h"
#include "stb_image.h"
#include <iostream>
#include "Core/World.h"

void Texture::Bind()
{
    GLCALL(glActiveTexture(GL_TEXTURE0 + m_Slot))
    GLCALL(glBindTexture(TexType, m_Id))
}

void Texture::Unbind() const {
    GLCALL(glBindTexture(TexType, 0))}

Texture::~Texture(){
    GLCALL(glDeleteTextures(1, &m_Id))}

Texture::Texture(const std::string &path) : TexType(GL_TEXTURE_2D)
{
    stbi_set_flip_vertically_on_load(true);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

    if (m_LocalBuffer)
    {

        GLCALL(glGenTextures(1, &m_Id))
        GLCALL(glBindTexture(TexType, m_Id))

        GLCALL(glTexParameteri(TexType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR))
        GLCALL(glTexParameteri(TexType, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
        GLCALL(glTexParameteri(TexType, GL_TEXTURE_WRAP_S, GL_REPEAT))
        GLCALL(glTexParameteri(TexType, GL_TEXTURE_WRAP_T, GL_REPEAT))

        GLCALL(glTexImage2D(TexType, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer))
        glGenerateMipmap(TexType);

        // 如果还启用各向异性过滤
        if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
        {
            GLfloat anisoSetting = 0.0f;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
            glTexParameterf(TexType, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
        }

        stbi_image_free(m_LocalBuffer);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

std::unique_ptr<Texture> Texture::CreateDepthTexture()
{
    auto p = std::make_unique<Texture>(GL_TEXTURE_2D);

    int screenSizeX, screenSizeY;
    world.GetWindow()->GetFrameBufferSize(screenSizeX, screenSizeY);
    glTexImage2D(p->TexType, 0, GL_DEPTH_COMPONENT, screenSizeX, screenSizeY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(p->TexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(p->TexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(p->TexType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(p->TexType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(p->TexType, GL_TEXTURE_BORDER_COLOR, borderColor);

    return p;
}

std::unique_ptr<Texture> Texture::CreateCubeMap(const char *map_path[])
{
    auto p = std::make_unique<Texture>(GL_TEXTURE_CUBE_MAP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    int width, height, nrchannels;
    for (int i = 0; i < 6; i++)
    {
        const char *path = map_path[i];

        unsigned char *buffer = stbi_load(path, &width, &height, &nrchannels, 0);

        if (buffer)
        {

            GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer))
        }
        else
        {
            ERROR("Fail to load texture image")
        }

        stbi_image_free(buffer);
    }

    return p;
}

Texture::Texture(GLenum Type) : TexType(Type)
{
    static int slot_id = 0;
    m_Slot = slot_id++;

    GLCALL(glGenTextures(1, &m_Id))
    Bind();
}
