#pragma once
#include <includes.h>

namespace Vista {

class IShader {
public:
    virtual ~IShader() = default;

    // --- Shader Binding Control ---
    virtual void bind() = 0;
    virtual void unbind() = 0;

    // --- Uniform Setters ---
    virtual void setUniform(const std::string& name, int value) = 0;
    virtual void setUniform(const std::string& name, float value) = 0;
    virtual void setUniform(const std::string& name, const glm::vec3& value) = 0;
    virtual void setUniform(const std::string& name, const glm::vec4& value) = 0;
    virtual void setUniform(const std::string& name, const glm::mat3& value) = 0;
    virtual void setUniform(const std::string& name, const glm::vec2& value) = 0;
    virtual void setUniform(const std::string& name, const glm::mat4& value) = 0;
};

}