#pragma once

#include "../config.h"

unsigned int linkShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
unsigned int compileModule(const std::string &filepath, unsigned int moduleType);