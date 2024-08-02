#include "engine.h"

const unsigned int WINWIDTH = 640;
const unsigned int WINHEIGHT = 480;

Engine::Engine(){
    setupGLFW();
}

Engine::~Engine(){
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    glDeleteBuffers(VBOs.size(), VBOs.data());
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

unsigned int Engine::createEntity(){
    return entityID++;
}

unsigned int Engine::makeCube(float s){
    std::vector<float> vertices = {
         s,  s, -s, 1.0f, 1.0f,
         s, -s, -s, 1.0f, 0.0f,
        -s, -s, -s, 0.0f, 0.0f,
        -s, -s, -s, 0.0f, 0.0f,
        -s,  s, -s, 0.0f, 1.0f,
         s,  s, -s, 1.0f, 1.0f,

        -s, -s,  s, 0.0f, 0.0f,
         s, -s,  s, 1.0f, 0.0f,
         s,  s,  s, 1.0f, 1.0f,
         s,  s,  s, 1.0f, 1.0f,
        -s,  s,  s, 0.0f, 1.0f,
        -s, -s,  s, 0.0f, 0.0f,

        -s,  s,  s, 1.0f, 1.0f,
        -s,  s, -s, 1.0f, 0.0f,
        -s, -s, -s, 0.0f, 0.0f,
        -s, -s, -s, 0.0f, 0.0f,
        -s, -s,  s, 0.0f, 1.0f,
        -s,  s,  s, 1.0f, 1.0f,

         s, -s, -s, 0.0f, 0.0f,
         s,  s, -s, 1.0f, 0.0f,
         s,  s,  s, 1.0f, 1.0f,
         s,  s,  s, 1.0f, 1.0f,
         s, -s,  s, 0.0f, 1.0f,
         s, -s, -s, 0.0f, 0.0f,

        -s, -s, -s, 0.0f, 0.0f,
         s, -s, -s, 1.0f, 0.0f,
         s, -s,  s, 1.0f, 1.0f,  
         s, -s,  s, 1.0f, 1.0f,
        -s, -s,  s, 0.0f, 1.0f,
        -s, -s, -s, 0.0f, 0.0f,

         s,  s,  s, 1.0f, 1.0f,
         s,  s, -s, 1.0f, 0.0f,
        -s,  s, -s, 0.0f, 0.0f, 
        -s,  s, -s, 0.0f, 0.0f,
        -s,  s,  s, 0.0f, 1.0f,
         s,  s,  s, 1.0f, 1.0f
    };
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
    glEnableVertexAttribArray(0);
    
    return VAO;
}

void Engine::run(){
    while(!glfwWindowShouldClose(window)){        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        cameraSystem->update(transformComponents, cameraID, cameraComponent);
        renderSystem->update(renderComponents);
    }
}

void Engine::setupOpenGL(){
    glClearColor(0.21f, 0.02f, 0.12f, 1.0f);

	int w,h;
	glfwGetFramebufferSize(window, &w, &h);
	std::cout << "w:" << w << "\nh:" << h << std::endl;
	glViewport(0,0,w,h);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    shader = linkShader(
        "../src/shaders/vertex.glsl",
        "../src/shaders/fragment.glsl");

    glUseProgram(shader);
}

void Engine::setupGLFW(){
    if(!glfwInit()){
        std::cerr << "Error loading GLFW.";
        glfwSetWindowShouldClose(window, true);
    }

    // Requires at least OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    
    window = glfwCreateWindow(WINWIDTH, WINHEIGHT, "Jynx Graphics Engine", NULL, NULL);
    if(!window){
        glfwTerminate();
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
    
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to load OpenGL." << std::endl;
        glfwTerminate();
    }
}

void Engine::makeSystems(){
    renderSystem = new RenderSystem(window);
}
