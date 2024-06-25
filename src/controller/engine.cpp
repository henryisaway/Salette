#include "engine.h"

const unsigned int WINWIDTH = 640;
const unsigned int WINHEIGHT = 480;

Engine::Engine(){
    glfwSetup();
}

Engine::~Engine(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::run(){
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
}

void Engine::initOpenGL(){
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

	int w,h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0,0,w,h);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
}

void Engine::glfwSetup(){
    if(!glfwInit()){
        std::cerr << "Error loading GLFW.";
        glfwSetWindowShouldClose(window, true);
    }

    // Requires at least OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    
    window = glfwCreateWindow(WINWIDTH, WINHEIGHT, "Mira Graphics Engine", NULL, NULL);
    if(!window){
        glfwTerminate();
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
    
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        std::cerr << "Failed to load OpenGL." << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
}
