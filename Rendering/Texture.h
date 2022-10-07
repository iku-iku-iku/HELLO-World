//
// Created by code4love on 2022/9/4.
//

#ifndef HELLO_TEXTURE_H
#define HELLO_TEXTURE_H

#include <string>
#include <memory>

class Texture {
private:
    unsigned int m_Id{};
    int m_Width{};
    int m_Height{};
    unsigned char *m_LocalBuffer{};
    int m_BPP{};
    unsigned int m_Slot{};
public:
    typedef unsigned int GLenum;
    Texture(GLenum Type);

    Texture(const std::string &path);

    ~Texture();

    void Bind();

    void Unbind() const;

    unsigned int GetId() const { return m_Id; }

    unsigned int GetSlot() const { return m_Slot; }

    const GLenum TexType;

    static std::unique_ptr<Texture> CreateTexture();

    static std::unique_ptr<Texture> CreateDepthTexture();

    static std::unique_ptr<Texture> CreateCubemap(const char* map_path[]);
};

#endif //HELLO_TEXTURE_H
