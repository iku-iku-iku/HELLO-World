//
// Created by code4love on 2022/9/10.
//

#ifndef HELLO_RENDERUTILS_H
#define HELLO_RENDERUTILS_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace RenderUtils {

    inline glm::mat4 GetRotationMatrix(glm::vec3 rotation) {
        glm::mat4 viewRot = glm::mat4(1.f);
        viewRot *= glm::rotate(glm::mat4(1.f), rotation.x, glm::vec3(1.f, 0.f, 0.f));
        viewRot *= glm::rotate(glm::mat4(1.f), rotation.y, glm::vec3(0.f, 1.f, 0.f));
        viewRot *= glm::rotate(glm::mat4(1.f), rotation.z, glm::vec3(0.f, 0.f, 1.f));
        return viewRot;
    }
}

#endif //HELLO_RENDERUTILS_H
