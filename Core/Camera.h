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

        const glm::mat4 &GetProjection() const { return m_Proj; }

        const glm::mat4 &GetView() const;

        glm::mat4 GetProjectionView() const { return GetProjection() * GetView(); }

        void SetProjection(float fov, float aspect, float zNear, float zFar);

        void SetTranslation(float x, float y, float z);

        void AddTranslation(float x, float y, float z);

        void OnImGuiRender();

        glm::vec3 GetDirection() const;

        glm::vec3 GetRight() const;

        Rotation &GetRotation() { return m_ViewRotation; }

    private:
        mutable Rotation m_Pitch{};
        mutable Matrix4f m_View{};
        glm::vec3 m_ViewTranslation{};
        Rotation m_ViewRotation{};
        glm::mat4 m_Proj{};
    };

}
