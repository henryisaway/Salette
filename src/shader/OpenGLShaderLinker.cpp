#include "../../include/shader/OpenGLShaderLinker.h"

namespace Vista {

std::unique_ptr<IShader> OpenGLShaderLinker::createShader(const std::string& vertexPath, const std::string& fragmentPath){
    return std::make_unique<OpenGLShader>(linkProgram(vertexPath, fragmentPath));
}

// This links all compiled shader modules together
unsigned int OpenGLShaderLinker::linkProgram(const std::string &vertexFilepath, const std::string &fragmentFilepath){
    
    // Packs vertex and fragment shaders together in a vector
    std::vector<unsigned int> modules;
    modules.push_back(compileShaderModule(vertexFilepath, GL_VERTEX_SHADER));
    modules.push_back(compileShaderModule(fragmentFilepath, GL_FRAGMENT_SHADER));
    
    
    unsigned int shader = glCreateProgram(); // Returns ID for the shader program
    
    // For each module in modules, attach the shader module in the program
    for(unsigned int shaderModule : modules){
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader); // Link all modules into the program
    
    // Error handling
    int shaderLinkSuccessful;
    glGetProgramiv(shader, GL_LINK_STATUS, &shaderLinkSuccessful);
    if(!shaderLinkSuccessful){
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        CLIO_FATAL("Shader linking error:\n", errorLog);
        exit(EXIT_FAILURE);
    }
    
    // Shaders aren't needed after linking, so they are all deleted
    for(unsigned int shaderModule : modules){
        glDeleteShader(shaderModule);
    }
    
    return shader;
}

// This loads the shader module
unsigned int OpenGLShaderLinker::compileShaderModule(const std::string &filepath, unsigned int moduleType){
    std::ifstream file; // file object
    std::stringstream bufferedLines; // object that stores multiple strings
    std::string line;
    
    file.open(filepath);
    while(std::getline(file, line)){
        bufferedLines << line << "\n"; // Store shader source code into stringstream object
    }
    
    std::string shaderSource = bufferedLines.str();
    const char* shaderSourceC = shaderSource.c_str(); // Convert stringstream into a c-style string pointer.
    
    bufferedLines.str(""); // Clears stringstream object
    file.close();
    
    // Compiling shader source code
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
    }
    
    return shaderModule;
}

}