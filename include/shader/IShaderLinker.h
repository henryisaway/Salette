#pragma once
#include <includes.h>
#include "IShader.h"

namespace Vista {

class IShaderLinker {
public:
    virtual ~IShaderLinker() = default;

    /**
     * @brief: abstracts the shader creation process from the
     *
     */
    virtual std::unique_ptr<IShader> createShader(const std::string& vertexPath, const std::string& fragmentPath) = 0;
};

}