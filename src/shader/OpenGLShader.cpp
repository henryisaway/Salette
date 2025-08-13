#include "../../include/shader/OpenGLShader.h"

namespace Salette {

OpenGLShader::OpenGLShader(GLuint programId) {
    this->m_ProgramId = programId;
    CLIO_INFO("OpenGL Shader created with ID ", m_ProgramId);
}

OpenGLShader::~OpenGLShader() {
    glDeleteProgram(m_ProgramId);
}

void OpenGLShader::bind() {
    CLIO_TRACE("Shader ", m_ProgramId, " was bound.");
    glUseProgram(m_ProgramId);
}

void OpenGLShader::unbind() {
    CLIO_TRACE("Shader ", m_ProgramId, " was unbound.");
    glUseProgram(0);
}

void OpenGLShader::setUniform(const std::string& name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void OpenGLShader::setUniform(const std::string& name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void OpenGLShader::setUniform(const std::string& name, const glm::vec2& value) {
    glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void OpenGLShader::setUniform(const std::string& name, const glm::vec3& value) {
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void OpenGLShader::setUniform(const std::string& name, const glm::vec4& value) {
    glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void OpenGLShader::setUniform(const std::string& name, const glm::mat3& value) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::setUniform(const std::string& name, const glm::mat4& value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

GLint OpenGLShader::getUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    GLint location = glGetUniformLocation(m_ProgramId, name.c_str());
    if (location == -1) {
        CLIO_WARN("Uniform '", name, "' not found.");
    }
    m_UniformLocationCache[name] = location;
    return location;
}

} // namespace Vista
