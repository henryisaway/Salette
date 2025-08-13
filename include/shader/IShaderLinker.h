#pragma once
#include <includes.h>
#include "IShader.h"

namespace Salette {

class IShaderLinker {
public:
    virtual ~IShaderLinker() = default;

    virtual std::unique_ptr<IShader> createShader(const std::string& vertexPath, const std::string& fragmentPath) = 0;
};

}