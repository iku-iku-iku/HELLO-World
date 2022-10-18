//
// Created by code4love on 2022/9/10.
//

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "core/Window.h"
#include "world/World.h"

namespace core {
    void Camera::OnImGuiRender() {
        if (ImGui::SliderFloat3("View Translation", &m_ViewTranslation.x, -10.f, 10.f)) {
        }
    }

    void Camera::SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar) {
        m_PerspectiveProjection = glm::perspective(fov, aspect, zNear, zFar);
    }

    void Camera::SetOrthographicProjection(float left, float right, float bottom, float top) {
        m_OrthographicProjection = glm::ortho(left, right, bottom, top);
    }

    void Camera::SetTranslation(float x, float y, float z) {
        m_ViewTranslation.x = x;
        m_ViewTranslation.y = y;
        m_ViewTranslation.z = z;
    }

    Camera::Camera() {
        int width, height;
        world->GetWindow()->GetFrameBufferSize(width, height);
        SetPerspectiveProjection(1.3f, (float) width / (float) height, .1f, 100.f);

        float widthHeightRatio = world->GetWindow()->GetWidthHeightRatio();
        SetOrthographicProjection(-5.f * widthHeightRatio, 5.f * widthHeightRatio, -5.f, 5.f);
        SetTranslation(0.f, 1.f, 5.f);
    }

    const glm::mat4 &Camera::GetView() const {
        // if not dirty, then use the previously computed one
        m_View = m_ViewRotation.GetInv() * glm::translate(glm::mat4(1.f), -m_ViewTranslation);
        return m_View;
    }

    void Camera::AddTranslation(float x, float y, float z) {
        SetTranslation(m_ViewTranslation.x + x,
                       m_ViewTranslation.y + y,
                       m_ViewTranslation.z + z);
    }

    glm::vec3 Camera::GetDirection() const {
        return m_ViewRotation.GetMat() * glm::vec4(0, 0, -1, 0);
    }

    glm::vec3 Camera::GetRight() const {
        return m_ViewRotation.GetYawMatrix() * glm::vec4(1, 0, 0, 0);
    }
}
