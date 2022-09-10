//
// Created by code4love on 2022/9/10.
//

#ifndef HELLO_CAMERA_H
#define HELLO_CAMERA_H

#include "glm/glm.hpp"

class Camera {
public:
    Camera();

    const glm::mat4 &GetProjection() const { return m_Proj; }

    const glm::mat4 &GetView() const;

    const glm::mat4 GetProjectionView() const { return GetProjection() * GetView(); }

    void SetProjection(float fov, float aspect, float zNear, float zFar);

    void SetTranslation(float x, float y, float z);

    void OnImGuiRender();

private:
    mutable glm::mat4 m_View{};
    glm::vec3 m_ViewTranslate{};
    glm::vec3 m_ViewRotation{};
    glm::mat4 m_Proj{};

    mutable bool m_ViewDirty = true;
};

#endif //HELLO_CAMERA_H
