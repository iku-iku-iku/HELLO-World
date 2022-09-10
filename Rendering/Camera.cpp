//
// Created by code4love on 2022/9/10.
//

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "RenderUtils.h"

extern GLFWwindow *window;

void Camera::OnImGuiRender() {
    if (ImGui::SliderFloat3("View Translation", &m_ViewTranslate.x, -10.f, 10.f)) {
        m_ViewDirty = true;
    }
    if (ImGui::SliderFloat3("View Rotation", &m_ViewRotation.x, -M_PI, M_PI)) {
        m_ViewDirty = true;
    }
}

void Camera::SetProjection(float fov, float aspect, float zNear, float zFar) {
    m_Proj = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::SetTranslation(float x, float y, float z) {
    m_ViewTranslate = {x, y, z};
}

Camera::Camera() {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    SetProjection(1.3f, (float) width / (float) height, .1f, 100.f);
    SetTranslation(0.f, 0.f, 15.f);
}

const glm::mat4 &Camera::GetView() const {
    if (!m_ViewDirty) { return m_View; }

    m_View = glm::transpose(RenderUtils::GetRotationMatrix(m_ViewRotation));
    m_View *= glm::translate(glm::mat4(1.f), -m_ViewTranslate);

    m_ViewDirty = false;
    return m_View;
}
