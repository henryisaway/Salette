#include "../../include/shader/OpenGLShaderLinker.h"

namespace Salette {

std::unique_ptr<IShader> OpenGLShaderLinker::createShader(const std::string& vertexPath, const std::string& fragmentPath){
    return std::make_unique<OpenGLShader>(linkProgram(vertexPath, fragmentPath));
}

// This links all compiled shader modules together
unsigned int OpenGLShaderLinker::linkProgram(const std::string &vertexFilepath, const std::string &fragmentFilepath){
    
    std::vector<unsigned int> modules;
    modules.push_back(compileShaderModule(vertexFilepath, GL_VERTEX_SHADER));
    modules.push_back(compileShaderModule(fragmentFilepath, GL_FRAGMENT_SHADER));
    
    unsigned int shaderProgram = glCreateProgram();
    
    for(unsigned int shaderModule : modules){
        glAttachShader(shaderProgram, shaderModule);
    }

    glLinkProgram(shaderProgram);
    
    // Error handling
    int shaderLinkSuccessful;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderLinkSuccessful);
    if(!shaderLinkSuccessful){
        char errorLog[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, errorLog);
        CLIO_FATAL("Shader linking error: ", errorLog);
        exit(EXIT_FAILURE);
    }

    for(unsigned int shaderModule : modules){
        glDeleteShader(shaderModule);
    }
    
    CLIO_DEBUG("OpenGL Shader Linker has finished shader compilation with ID ", shaderProgram);
    return shaderProgram;
}

unsigned int OpenGLShaderLinker::compileShaderModule(const std::string &filepath, unsigned int moduleType){
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;
    
    file.open(filepath);
    while(std::getline(file, line)){
        bufferedLines << line << "\n";
    }
    
    std::string shaderSource = bufferedLines.str();
    const char* shaderSourceC = shaderSource.c_str();
    
    file.close();
    
    unsigned int shaderModule = glCreateShader(moduleType);
    glShaderSource(shaderModule, 1, &shaderSourceC, NULL); // Input souce code
    glCompileShader(shaderModule);
    
    // Error handling
    int shaderCompilationSuccessful;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &shaderCompilationSuccessful);
    if(!shaderCompilationSuccessful){
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        CLIO_FATAL("Shader Module compilation error:\n", errorLog);
        exit(EXIT_FAILURE);
    }
    
    return shaderModule;
}

}