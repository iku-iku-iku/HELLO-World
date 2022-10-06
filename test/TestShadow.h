//
// Created by code4love on 2022/9/6.
//

#ifndef HELLO_TESTSHADOW_H
#define HELLO_TESTSHADOW_H

#include <Core/World.h>
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
#include "Plane.h"
#include "FrameBuffer.h"

namespace test {
    class TestShadow : public Test {
    public:
        TestShadow();

        ~TestShadow() override;

        void OnUpdate(float deltaTime) override;

        void OnRender(float currentTime) override;

        void OnImGuiRender() override;


    private:
        std::unique_ptr<FrameBuffer> m_FrameBuffer;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader1;
        std::unique_ptr<Shader> m_Shader2;
        std::unique_ptr<Texture> m_DepthMap;
        std::unique_ptr<Renderer> m_Renderer;

        core::World m_World;

        Ring m_Ring;
        Plane m_Plane;
    };
}

#endif //HELLO_TESTSHADOW_H
