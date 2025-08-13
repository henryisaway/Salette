#pragma once

#include <includes.h>
#include "IShaderLinker.h"
#include "OpenGLShader.h"

namespace Salette {

class OpenGLShaderLinker : public IShaderLinker {
public:

    std::unique_ptr<IShader> createShader(const std::string& vertexPath, const std::string& fragmentPath) override;

private:
    unsigned int linkProgram(const std::string& vertexFilepath, const std::string& fragmentFilepath);
    unsigned int compileShaderModule(const std::string &filepath, unsigned int moduleType);
};

}