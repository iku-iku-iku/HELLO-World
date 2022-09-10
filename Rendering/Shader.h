//
// Created by code4love on 2022/9/2.
//

#ifndef HELLO_SHADER_H
#define HELLO_SHADER_H

#include <iostream>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderSource {
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader {
private:
    mutable std::unordered_map<std::string, int> uniform_location_cache;

    std::string m_source_path;

    unsigned int m_id;

    static ShaderSource ParseShaderSource(const std::string &shader_path);

    static unsigned int CompileShader(unsigned int type, const std::string &source);

    static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

    int GetUniformLocation(const std::string &uniform_name) const;

public:
    Shader(const char *shader_path);

    ~Shader();

    void Bind() const;

    void UnBind() const;

    void SetUniform4f(const std::string &uniform_name, float r, float g, float b, float a);

    void SetUniformMat4f(const std::string &uniform_name, const glm::mat4 &mat);

    void SetUniform1i(const std::string &uniform_name, int i);

    void SetUniform4fv(const std::string &uniform_name, float* data);

    void SetUniform1f(const std::string &uniform_name, float data);

    void SetUniform3fv(const std::string &uniform_name, float* data);
};

#endif //HELLO_SHADER_H
