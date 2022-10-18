//
// Created by code4love on 2022/10/17.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "core/Log.h"
#include "glm/glm.hpp"


namespace rhi {


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

        void Bind() const;

        void Unbind() const;

        unsigned int GetId() const { return m_Id; }

        unsigned int GetSlot() const { return m_Slot; }

        const GLenum TexType;

        static std::unique_ptr<Texture> CreateTexture();

        static std::unique_ptr<Texture> CreateDepthTexture();

        static std::unique_ptr<Texture> CreateCubeMap(const char *map_path[]);
    };


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

        static void AttachDepth(const Texture &texture);

        GLuint GetId() const { return m_Id; }

        void DisableDraw() const;

        void DisableRead() const;

        void ClearDepthBuffer() const;

        void CheckBound() const;


    private:
        GLuint m_Id{};

        static GLuint CurrentId;
    };


    class IndexBuffer {
        typedef unsigned int IndexType;
    private:
        unsigned int m_id{};
        unsigned int m_Count{};

    public:
        IndexBuffer(const unsigned int *data, unsigned int count);

        IndexBuffer();

        ~IndexBuffer();

        void Bind() const;

        static void UnBind() ;

        void Allocate(const unsigned int MaxIndexCnt);

        void SetData(const unsigned int *data, unsigned int count);

        inline unsigned int GetCount() const { return m_Count; }

    private:
        unsigned int m_MaxIndexCnt{};
    };


    class Shader {
    private:
        struct ShaderSource {
            std::string VertexShader;
            std::string FragmentShader;
        };

        mutable std::unordered_map<std::string, int> uniform_location_cache;

        std::string m_source_path;

        unsigned int m_id;

        static ShaderSource ParseShaderSource(const std::string &shader_path);

        static unsigned int CompileShader(unsigned int type, const std::string &source);

        static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

        int GetUniformLocation(const std::string &uniform_name) const;

    public:
        Shader(const char *shader_path);

        ~Shader();

        void Bind() const;

        static void UnBind() ;

        void SetUniform4f(const std::string &uniform_name, float r, float g, float b, float a);

        void SetUniformMat4f(const std::string &uniform_name, const glm::mat4 &mat);

        void SetUniform1i(const std::string &uniform_name, int i);

        void SetUniform4fv(const std::string &uniform_name, float *data);

        void SetUniform1f(const std::string &uniform_name, float data);

        void SetUniform3fv(const std::string &uniform_name, float *data);
    };

    class VertexBuffer {
    private:
        unsigned int m_id{};

    public:
        VertexBuffer(const void *data, unsigned int size);

        VertexBuffer();

        ~VertexBuffer();

        void Allocate(const unsigned int MaxBufferSize);

        void SetData(const void *data, unsigned int size) const;

        void Bind() const;

        static void UnBind() ;

    private:
        unsigned int m_MaxBufferSize{};
    };


    struct VertexBufferElement {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetTypeSize(unsigned int type) {
            switch (type) {
                case GL_FLOAT:
                    return 4;

                case GL_UNSIGNED_INT:
                    return 4;

                case GL_UNSIGNED_BYTE:
                    return 1;

                default:
                    return 0;
            }
        }
    };

    class VertexBufferLayout {
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;

    public:
        VertexBufferLayout() : m_Stride(0) {}

        template<typename T>
        void Push(unsigned int count);

        inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }

        inline unsigned int GetStride() const { return m_Stride; }
    };

    class VertexArray {
    private:
        unsigned int m_id{};
    public:
        VertexArray(/* args */);

        ~VertexArray();

        void Bind() const;

        static void UnBind();

        void SetBuffer(const VertexBuffer &vb, const rhi::VertexBufferLayout &layout) const;
    };

    class Renderer {
    public:
        Renderer();

        static void Clear();

        static void ClearColor();

        void Render(const Shader &shader) const;

        void RenderDepthMap();

    protected:
        std::unique_ptr<FrameBuffer> m_FrameBuffer;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Texture> m_DepthMap;
        std::unique_ptr<Shader> m_DepthRenderingShader;

        static void InitOpenGLEnv();
    };


    template<typename T>
    void VertexBufferLayout::Push(unsigned int count) {
    }

    template<>
    inline void VertexBufferLayout::Push<float>(unsigned int count) {
        m_Elements.push_back({GL_FLOAT, count, false});
        m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
    }
}
