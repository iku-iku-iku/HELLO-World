//
// Created by code4love on 2022/9/4.
//

#ifndef HELLO_TEXTURE_H
#define HELLO_TEXTURE_H

#include <string>

class Texture {
private:
    unsigned int m_Id;
    int m_Width;
    int m_Height;
    unsigned char *m_LocalBuffer;
    int m_BPP;
public:
    Texture(const std::string &path);

    ~Texture();

    void Bind(unsigned int slot = 0) const;

    void Unbind() const;
};

#endif //HELLO_TEXTURE_H
