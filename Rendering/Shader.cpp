//
// Created by code4love on 2022/9/2.
//

#include "Shader.h"
#include "Rendering/Renderer.h"
#include <fstream>
#include <sstream>

Shader::Shader(const char *shader_path) : m_source_path(shader_path) {
    ShaderSource source = ParseShaderSource(shader_path);
    m_id = CreateShader(source.VertexShader, source.FragmentShader);
    glUseProgram(m_id);
}

ShaderSource Shader::ParseShaderSource(const std::string &shader_path) {
    std::ifstream stream(shader_path);

    std::string line;

    enum class ShaderType {
        None = -1,
        Vertex = 0,
        Fragment = 1
    };

    ShaderType type = ShaderType::None;

    std::stringstream ss[2];

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::Vertex;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::Fragment;
            }
        } else {
            ss[(int) type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::UnBind() const {
    GLCALL(glUseProgram(0))
}

void Shader::Bind() const {
    GLCALL(glUseProgram(m_id))
}

Shader::~Shader() {
    GLCALL(glDeleteProgram(m_id))
}

void Shader::SetUniform4f(const std::string &uniform_name, float r, float g, float b, float a) {
    GLCALL(glUniform4f(GetUniformLocation(uniform_name), r, g, b, a))
}

int Shader::GetUniformLocation(const std::string &uniform_name) const {
    if (uniform_location_cache.find(uniform_name) != uniform_location_cache.end()) {
        return uniform_location_cache[uniform_name];
    }
    GLCALL(int location = glGetUniformLocation(m_id, uniform_name.c_str()))
    if (location == -1) {
        std::cout << "WARNING: uniform '" << uniform_name << "' doesn't exist!" << std::endl;
    }

    uniform_location_cache[uniform_name] = location;
    return location;
}

void Shader::SetUniform1i(const std::string &uniform_name, int i) {
    GLCALL(glUniform1i(GetUniformLocation(uniform_name), i))
}

void Shader::SetUniformMat4f(const std::string &uniform_name, const glm::mat4 &mat) {
    GLCALL(glUniformMatrix4fv(GetUniformLocation(uniform_name), 1, GL_FALSE, &mat[0][0]))
}

void Shader::SetUniform4fv(const std::string &uniform_name, float *data) {
    GLCALL(glUniform4fv(GetUniformLocation(uniform_name), 1, data))
}

void Shader::SetUniform1f(const std::string &uniform_name, float data) {
    GLCALL(glUniform1f(GetUniformLocation(uniform_name), data))
}

void Shader::SetUniform3fv(const std::string &uniform_name, float *data) {
    GLCALL(glUniform3fv(GetUniformLocation(uniform_name), 1, data))
}
