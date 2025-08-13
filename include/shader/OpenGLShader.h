#pragma once

#include <includes.h>
#include "IShader.h"

namespace Salette {

class OpenGLShader : public IShader {
public:
    /**
     * @brief Constructs and compiles a shader program from vertex and fragment shader files.
     * @param vertexPath Path to the vertex shader source file.
     * @param fragmentPath Path to the fragment shader source file.
     */
    OpenGLShader(GLuint programId);

    /**
     * @brief Destructor that deletes the shader program.
     */
    ~OpenGLShader();

    // --- Shader Binding ---
    void bind() override;
    void unbind() override;

    // --- Uniform Setters ---
    void setUniform(const std::string& name, int value) override;
    void setUniform(const std::string& name, float value) override;
    void setUniform(const std::string& name, const glm::vec2& value) override;
    void setUniform(const std::string& name, const glm::vec3& value) override;
    void setUniform(const std::string& name, const glm::vec4& value) override;
    void setUniform(const std::string& name, const glm::mat3& value) override;
    void setUniform(const std::string& name, const glm::mat4& value) override;

private:
    GLint getUniformLocation(const std::string& name);

    GLuint m_ProgramId = 0;
    std::unordered_map<std::string, GLint> m_UniformLocationCache;
};
}