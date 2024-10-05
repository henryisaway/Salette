#include "engine.h"
#include "../stb_image.h"

const unsigned int WINWIDTH = 640;
const unsigned int WINHEIGHT = 480;

Engine::Engine(){
    setupGLFW();
}

Engine::~Engine(){
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    glDeleteBuffers(VBOs.size(), VBOs.data());
    glDeleteTextures(textures.size(), textures.data());
    glDeleteProgram(shader);
    
    delete motionSystem;
    delete cameraSystem;
    delete renderSystem;
    
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

    // Position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
    glEnableVertexAttribArray(1);
    
    return VAO;
}

void Engine::run(){
    while(!glfwWindowShouldClose(window)){        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        
        motionSystem->update(transformComponents, physicsComponents, 16.67f/1000.0f);        
        cameraSystem->update(transformComponents, cameraID, *cameraComponent);
        renderSystem->update(renderComponents, transformComponents);
    }
}

unsigned int Engine::makeTexture(const char* filename){
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);
    
    // Making texture
    unsigned int texture;
    glGenTextures(1, &texture);
    textures.push_back(texture); // This is just a vector don't panic
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    stbi_image_free(data);
    
    // Sampler settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    return texture;
}

void Engine::setupOpenGL(){
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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
    
    float FOV = 45.0f;
    unsigned int projectionLocation = glGetUniformLocation(shader, "projection");
    glm::mat4 projection = glm::perspective(FOV, (float)WINWIDTH/(float)WINHEIGHT, 0.1f, 10.0f);
    
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
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
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Engine::makeSystems(){
    motionSystem = new MotionSystem();
    cameraSystem = new CameraSystem(window, shader);
    renderSystem = new RenderSystem(window, shader);
}
