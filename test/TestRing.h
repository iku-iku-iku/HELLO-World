//
// Created by code4love on 2022/9/6.
//

#ifndef HELLO_TESTRING_H
#define HELLO_TESTRING_H

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
#include "Core/Camera.h"
#include "Ring.h"

namespace test {
    class TestRing : public Test {
    public:
        TestRing();

        ~TestRing() override;

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

        core::Camera m_Camera;
        Ring m_Ring;
    };
}

#endif //HELLO_TESTRING_H
