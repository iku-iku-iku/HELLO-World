//
// Created by code4love on 2022/10/17.
//

#include <fstream>
#include "OpenGLAPI.h"
#include "Core/Log.h"
#include <sstream>
#include "stb_image.h"
#include "Core/World.h"
#include "WorldRenderer.h"

namespace rhi {

    GLuint rhi::FrameBuffer::CurrentId = 0;

    rhi::FrameBuffer::FrameBuffer() {
        GLCALL(glGenFramebuffers(1, &m_Id))
    }

    rhi::FrameBuffer::~FrameBuffer() {
        GLCALL(glDeleteFramebuffers(1, &m_Id))
    }

    void rhi::FrameBuffer::Bind() const {
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_Id))
        CurrentId = m_Id;
    }

    bool rhi::FrameBuffer::IsComplete() {
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }

    void rhi::FrameBuffer::AttachDepth(const Texture &texture) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.GetId(), 0);
    }

    void rhi::FrameBuffer::DisableDraw() const {
        CheckBound();
        glDrawBuffer(GL_NONE);
    }

    void rhi::FrameBuffer::DisableRead() const {
        CheckBound();
        glReadBuffer(GL_NONE);
    }

    void rhi::FrameBuffer::CheckBound() const {
        REQUIRE(CurrentId == m_Id)
    }

    void rhi::FrameBuffer::ClearDepthBuffer() const {
        CheckBound();
        GLCALL(glClear(GL_DEPTH_BUFFER_BIT))
    }

    void rhi::Texture::Bind() const {
        GLCALL(glActiveTexture(GL_TEXTURE0 + m_Slot))
        GLCALL(glBindTexture(TexType, m_Id))
    }

    void rhi::Texture::Unbind() const {
        GLCALL(glBindTexture(TexType, 0))
    }

    rhi::Texture::~Texture() {
        GLCALL(glDeleteTextures(1, &m_Id))
    }

    rhi::Texture::Texture(const std::string &path) : TexType(GL_TEXTURE_2D) {
        stbi_set_flip_vertically_on_load(true);
        m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

        if (m_LocalBuffer) {

            GLCALL(glGenTextures(1, &m_Id))
            GLCALL(glBindTexture(TexType, m_Id))

            GLCALL(glTexParameteri(TexType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR))
            GLCALL(glTexParameteri(TexType, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
            GLCALL(glTexParameteri(TexType, GL_TEXTURE_WRAP_S, GL_REPEAT))
            GLCALL(glTexParameteri(TexType, GL_TEXTURE_WRAP_T, GL_REPEAT))

            GLCALL(glTexImage2D(TexType, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer))
            glGenerateMipmap(TexType);

            // 如果还启用各向异性过滤
            if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
                GLfloat anisoSetting = 0.0f;
                glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
                glTexParameterf(TexType, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
            }

            stbi_image_free(m_LocalBuffer);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
    }

    std::unique_ptr<rhi::Texture> rhi::Texture::CreateDepthTexture() {
        auto p = std::make_unique<rhi::Texture>(GL_TEXTURE_2D);

        int screenSizeX, screenSizeY;
        world.GetWindow()->GetFrameBufferSize(screenSizeX, screenSizeY);
        glTexImage2D(p->TexType, 0, GL_DEPTH_COMPONENT, screenSizeX, screenSizeY, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                     nullptr);
        glTexParameteri(p->TexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(p->TexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(p->TexType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(p->TexType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = {1.0, 1.0, 1.0, 1.0};
        glTexParameterfv(p->TexType, GL_TEXTURE_BORDER_COLOR, borderColor);

        return p;
    }

    std::unique_ptr<rhi::Texture> rhi::Texture::CreateCubeMap(const char *map_path[]) {
        auto p = std::make_unique<rhi::Texture>(GL_TEXTURE_CUBE_MAP);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        int width, height, channels;
        for (int i = 0; i < 6; i++) {
            const char *path = map_path[i];

            unsigned char *buffer = stbi_load(path, &width, &height, &channels, 0);

            if (buffer) {

                GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB,
                                    GL_UNSIGNED_BYTE, buffer))
            } else {
                ERROR("Fail to load texture image")
            }

            stbi_image_free(buffer);
        }

        return p;
    }

    rhi::Texture::Texture(GLenum Type) : TexType(Type) {
        static int slot_id = 0;
        m_Slot = slot_id++;

        GLCALL(glGenTextures(1, &m_Id))
        Bind();
    }

    rhi::IndexBuffer::IndexBuffer() {
        GLCALL(glGenBuffers(1, &m_id));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    }

    rhi::IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count) {
        GLCALL(glGenBuffers(1, &m_id));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(IndexType), data, GL_STATIC_DRAW));
    }

    rhi::IndexBuffer::~IndexBuffer() {
        GLCALL(glDeleteBuffers(1, &m_id))
    }

    void rhi::IndexBuffer::Bind() const {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    }

    void rhi::IndexBuffer::UnBind() {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void rhi::IndexBuffer::SetData(const unsigned int *data, unsigned int count) {
        Bind();

        m_Count = count;

        GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(IndexType), data))
    }

    void rhi::IndexBuffer::Allocate(const unsigned int MaxIndexCnt) {
        Bind();

        m_MaxIndexCnt = MaxIndexCnt;
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCnt * sizeof(IndexType), nullptr, GL_DYNAMIC_DRAW));
    }

    rhi::Shader::Shader(const char *shader_path) : m_source_path(shader_path) {
        ShaderSource source = ParseShaderSource(shader_path);
        m_id = CreateShader(source.VertexShader, source.FragmentShader);
        glUseProgram(m_id);
    }

    rhi::Shader::ShaderSource rhi::Shader::ParseShaderSource(const std::string &shader_path) {
        std::ifstream stream(shader_path);

        std::string line;

        enum class ShaderType {
            None = -1,
            Vertex = 0,
            Fragment = 1
        };

        ShaderType type = ShaderType::None;

        std::stringstream ss[2];

        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::Vertex;
                } else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::Fragment;
                }
            } else {
                ss[static_cast<std::size_t>(type)] << line << '\n';
            }
        }

        return {ss[0].str(), ss[1].str()};
    }

    unsigned int rhi::Shader::CompileShader(unsigned int type, const std::string &source) {
        unsigned int id = glCreateShader(type);
        const char *src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *) alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    unsigned int rhi::Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    void rhi::Shader::UnBind() {
        GLCALL(glUseProgram(0))
    }

    void rhi::Shader::Bind() const {
        GLCALL(glUseProgram(m_id))
    }

    rhi::Shader::~Shader() {
        GLCALL(glDeleteProgram(m_id))
    }

    void rhi::Shader::SetUniform4f(const std::string &uniform_name, float r, float g, float b, float a) {
        GLCALL(glUniform4f(GetUniformLocation(uniform_name), r, g, b, a))
    }

    int rhi::Shader::GetUniformLocation(const std::string &uniform_name) const {
        Bind();

        if (uniform_location_cache.find(uniform_name) != uniform_location_cache.end()) {
            return uniform_location_cache[uniform_name];
        }
        GLCALL(int location = glGetUniformLocation(m_id, uniform_name.c_str()))
        if (location == -1) {
            std::cout << "WARNING: uniform '" << uniform_name << "' doesn't exist!" << std::endl;
        }

        uniform_location_cache[uniform_name] = location;
        return location;
    }

    void rhi::Shader::SetUniform1i(const std::string &uniform_name, int i) {
        GLCALL(glUniform1i(GetUniformLocation(uniform_name), i))
    }

    void rhi::Shader::SetUniformMat4f(const std::string &uniform_name, const glm::mat4 &mat) {
        GLCALL(glUniformMatrix4fv(GetUniformLocation(uniform_name), 1, GL_FALSE, &mat[0][0]))
    }

    void rhi::Shader::SetUniform4fv(const std::string &uniform_name, float *data) {
        GLCALL(glUniform4fv(GetUniformLocation(uniform_name), 1, data))
    }

    void rhi::Shader::SetUniform1f(const std::string &uniform_name, float data) {
        GLCALL(glUniform1f(GetUniformLocation(uniform_name), data))
    }

    void rhi::Shader::SetUniform3fv(const std::string &uniform_name, float *data) {
        GLCALL(glUniform3fv(GetUniformLocation(uniform_name), 1, data))
    }

    rhi::VertexArray::VertexArray() {
        GLCALL(glGenVertexArrays(1, &m_id))
    }

    rhi::VertexArray::~VertexArray() {
        GLCALL(glDeleteVertexArrays(1, &m_id))
    }

    void rhi::VertexArray::Bind() const {
        GLCALL(glBindVertexArray(m_id))
    }

    void rhi::VertexArray::UnBind() {
        GLCALL(glBindVertexArray(0))
    }

    void rhi::VertexArray::SetBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const {
        Bind();
        vb.Bind();

        unsigned int offset = 0;
        const auto &Elements = layout.GetElements();
        for (int i = 0; i < Elements.size(); i++) {
            const auto &element = Elements[i];
            GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                                         reinterpret_cast<const void *>(offset)))
            GLCALL(glEnableVertexAttribArray(i))
            offset += element.count * VertexBufferElement::GetTypeSize(element.type);
        }
    }

    rhi::VertexBuffer::VertexBuffer() {
        GLCALL(glGenBuffers(1, &m_id))
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id))
    }

    rhi::VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
        GLCALL(glGenBuffers(1, &m_id));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id))
        GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))
    }

    rhi::VertexBuffer::~VertexBuffer() {
        GLCALL(glDeleteBuffers(1, &m_id))
    }

    void rhi::VertexBuffer::Bind() const {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    }

    void rhi::VertexBuffer::UnBind() {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void rhi::VertexBuffer::SetData(const void *data, unsigned int size) const {
        Bind();

        GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data))
    }

    void rhi::VertexBuffer::Allocate(const unsigned int MaxBufferSize) {
        Bind();

        m_MaxBufferSize = MaxBufferSize;
        GLCALL(glBufferData(GL_ARRAY_BUFFER, MaxBufferSize, nullptr, GL_DYNAMIC_DRAW))
    }
}


namespace {
    float globalAmbient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    float lightAmbient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightPos[3] = {2.f, 2.f, 2.f};
    float goldAmbient[4] = {0.2473f, 0.1995f, 0.0745f, 1};
    float goldDiffuse[4] = {0.7516f, 0.6065f, 0.2265f, 1};
    float goldSpecular[4] = {0.6283f, 0.5559f, 0.3661f, 1};
    float goldShininess = 51.2f;
}

void rhi::Renderer::Render(const rhi::Shader &shader) const {
    shader.Bind();
    m_VertexArray->Bind();
    m_IndexBuffer->Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void rhi::Renderer::Clear() {
    GLCALL(glClear(GL_COLOR_BUFFER_BIT))
}

void rhi::Renderer::ClearColor() {
    GLCALL(glClearColor(0.f, 0.f, 0.f, 1.f))
}

rhi::Renderer::Renderer() {
    InitOpenGLEnv();
    // Init vertex buffer
    m_VertexBuffer = std::make_unique<rhi::VertexBuffer>();
    m_VertexBuffer->Allocate(100000);

    // Init index buffer
    m_IndexBuffer = std::make_unique<rhi::IndexBuffer>();
    m_IndexBuffer->Allocate(10000);

    // Init vertex array
    m_VertexArray = std::make_unique<rhi::VertexArray>();
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    m_VertexArray->SetBuffer(*m_VertexBuffer, layout);

    // Init frame buffer
    m_FrameBuffer = std::make_unique<rhi::FrameBuffer>();

    // Init depth map
    m_DepthMap = rhi::Texture::CreateDepthTexture();

    m_FrameBuffer->Bind();
    m_FrameBuffer->AttachDepth(*m_DepthMap);
    m_FrameBuffer->DisableDraw();
    m_FrameBuffer->DisableRead();
    m_FrameBuffer->UnBind();

    // Init shader used for rendering depth map
    m_DepthRenderingShader = std::make_unique<rhi::Shader>("../shaders/test_shadow1.shader");

    SUCCEED("Renderer Init")
}

void rhi::Renderer::RenderDepthMap() {
    GLCALL(glClear(GL_DEPTH_BUFFER_BIT))

    m_FrameBuffer->Bind();
    m_FrameBuffer->ClearDepthBuffer();

    glm::mat4 lightProj = world.GetPlayerCamera()->GetPerspectiveProjection();
    glm::mat4 lightView = glm::lookAt(glm::vec3(lightPos[0], lightPos[1], lightPos[2]), glm::vec3(0.f, 0.f, 0.f),
                                      glm::vec3(0.f, 1.f, 0.f));

    // avoid z-fighting when two face are too close
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.f, 4.f);
    ////
    {
        m_DepthRenderingShader->Bind();
        glm::mat4 view = lightView;
        glm::mat4 proj = lightProj;

        for (const auto &shape: world.GetShapes()) {
            shape->SetData(*m_VertexBuffer, *m_IndexBuffer);
            glm::mat4 mvp = proj * view * shape->GetModelMatrix();
            m_DepthRenderingShader->SetUniformMat4f("u_MVP", mvp);
            Render(*m_DepthRenderingShader);
        }
    }
    m_FrameBuffer->UnBind();
    glDisable(GL_POLYGON_OFFSET_FILL);
}

void rhi::Renderer::InitOpenGLEnv() {
    GLenum initRes = glewInit();
    if (GLEW_OK != initRes) {
        ERROR("glew init failed!")
    }

    // gl setting
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    SUCCEED("Init OpenGL Environment")
}

