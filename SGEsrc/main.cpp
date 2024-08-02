#include "config.h"
#include "triangleMesh.h"
#include "material.h"

// Declaring function prototypes
unsigned int compileModule(const std::string &filepath, unsigned int moduleType);
unsigned int linkShader(const std::string &vertexFilepath, const std::string & fragmentFilepath);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WINWIDTH = 700;
const unsigned int WINHEIGHT = 700;

int main(int, char**){    
    /*
    Creates a GLFWwindow instance.
    GLFWwindow is a struct defined in the GLFW source code, containing
    all of the information necessary to create cross-platform window
    handling.
    */
    GLFWwindow* window;

    if(!glfwInit()){ // Initialises GLFW
        std::cerr << "Error loading GLFW.";
        return -1;
    }
    
    // Requesting minimum OpenGL Core version (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Returns GLFWwindow*
    window = glfwCreateWindow(WINWIDTH, WINHEIGHT, "Mira Graphics Engine", NULL, NULL);
    if(!window){
        glfwTerminate();
        std::cerr << "Failed to create GLFW window." << std::endl;
        return -1;
    }
    
    /*
    Informs OpenGL that the code wants it to keep track and make changes
    to a specific window in its state machine. This is called a context.
    */
    glfwMakeContextCurrent(window);
    
    // Informe glfw which function to use when the window is resized.
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    /*
    Loads the GLAD library, which loads OpenGL and dependencies. It also
    asks for the address of the OpenGL procedures, which it gets from
    GLFW's glfwGetProcAddress call and then casting the return into a
    GLADloadproc type.
    */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        std::cerr << "Failed to load OpenGL." << std::endl;
        return -1;
    }

    // Boots the shader programs
    unsigned int shader = linkShader(
        "../src/shaders/vertex.glsl",
        "../src/shaders/fragment.glsl"
    );
    
    glViewport(0, 0, WINWIDTH, WINHEIGHT);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Tells OpenGL which colour to clear the screen to
    
    TriangleMesh *triangle = new TriangleMesh();
    Material *material = new Material("../img/test.png");
    //Material *mask = new Material("../img/test2.jpg");
    
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "material"), 0);
    //glUniform1i(glGetUniformLocation(shader, "mask"), 1);
    
    glm::vec3 up = {0.0f, 0.0f, 1.0f};
    glm::vec3 quadPos = {0.0f, 0.0f, 0.0f};
    glm::vec3 cameraPos = {3.0f, 0.0f, 2.0f};
    glm::vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
    unsigned int modelLocation = glGetUniformLocation(shader, "model");
    unsigned int viewLocation = glGetUniformLocation(shader, "view");
    unsigned int projectionLocation = glGetUniformLocation(shader, "projection");
    
    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    
    glm::mat4 projection = glm::perspective(
        45.0f, ((float)WINWIDTH / (float)WINHEIGHT), 0.1f, 10.0f);
    
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Main loop
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents(); // Queues and processes all events
        processInput(window);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, quadPos);
        model = glm::rotate(model, (float)glfwGetTime(), up);
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        
        glClear(GL_COLOR_BUFFER_BIT); // Clears the colour buffer to the set colour
        glUseProgram(shader); // Tells OpenGL which shader to utilise;
        material->use(0);
        //mask->use(1);
        triangle->draw();
        glfwSwapBuffers(window); // OpenGL uses double-buffering, so this updates the screen
    }

    glfwDestroyWindow(window);
    glDeleteProgram(shader);
    delete triangle;
    delete material;
    //delete mask;
    glfwTerminate();

    return 0;
}

// This links all compiled shader modules together
unsigned int linkShader(const std::string &vertexFilepath, const std::string & fragmentFilepath){
    
    // Packs vertex and fragment shaders together in a vector
    std::vector<unsigned int> modules;
    modules.push_back(compileModule(vertexFilepath, GL_VERTEX_SHADER));
    modules.push_back(compileModule(fragmentFilepath, GL_FRAGMENT_SHADER));
    
    
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
        std::cerr << "Shader linking error:\n" << errorLog << std::endl;
    }
    
    // Shaders aren't needed after linking, so they are all deleted
    for(unsigned int shaderModule : modules){
        glDeleteShader(shaderModule);
    }
    
    return shader;
}

// This loads the shader module
unsigned int compileModule(const std::string &filepath, unsigned int moduleType){
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
        std::cerr << "Shader Module compilation error:\n" << errorLog << std::endl;
    }
    
    return shaderModule;
}

// This function is called whenever the window is resized. It Resizes the viewport to math window size.
void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

// This function houses all user input processing.
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
