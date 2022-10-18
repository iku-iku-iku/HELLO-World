//
// Created by code4love on 2022/9/10.
//

#pragma once

#include "glm/glm.hpp"
#include "Type.h"

namespace core {

    class Camera {
    public:
        Camera();

        const glm::mat4 &GetPerspectiveProjection() const { return m_PerspectiveProjection; }

        const glm::mat4 &GetOrthographicProjection() const { return m_OrthographicProjection; }

        const glm::mat4 &GetView() const;

        glm::mat4 GetViewProjection3D() const { return GetPerspectiveProjection() * GetView(); }

        glm::mat4 GetViewProjection2D() const { return GetOrthographicProjection() * GetView(); }

        // 固定在屏幕上的元素应用的变换，不随相机移动而移动
        const glm::mat4 &GetStaticViewProjection2D() const { return GetOrthographicProjection(); }

        void SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar);

        void SetOrthographicProjection(float left, float right, float bottom, float top);

        void SetTranslation(float x, float y, float z);

        void AddTranslation(float x, float y, float z);

        void OnImGuiRender();

        glm::vec3 GetDirection() const;

        glm::vec3 GetRight() const;

        glm::vec3 GetTranslation() const { return m_ViewTranslation; }

        Rotation &GetRotation() { return m_ViewRotation; }

    private:
        mutable Rotation m_Pitch{};
        mutable Matrix4f m_View{};
        glm::vec3 m_ViewTranslation{};
        Rotation m_ViewRotation{};
        glm::mat4 m_PerspectiveProjection{};
        glm::mat4 m_OrthographicProjection{};
    };

}
