//
// Created by code4love on 2022/9/6.
//

#ifndef HELLO_TESTTEXTURE2D_H
#define HELLO_TESTTEXTURE2D_H

#include "Test.h"
#include "memory"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Rendering/Renderer.h"

namespace test {
    class TestTexture2D  : public Test {
    public:
        TestTexture2D();
        ~TestTexture2D() override;

        void OnUpdate(float deltaTime) override;

        void OnRender(float currentTime) override;

        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<Renderer> m_Renderer;
        glm::vec3 m_Translation;
        glm::mat4 m_View;
        glm::mat4 m_Proj;
    };
}

#endif //HELLO_TESTTEXTURE2D_H
