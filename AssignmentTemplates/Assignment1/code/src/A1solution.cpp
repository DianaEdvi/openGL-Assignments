#include "A1solution.h"

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

#include "Model.h"
#include "Shaders.h"

// void debug_gl(int place){
//     GLenum e = glGetError();
//     if(e!=GL_NO_ERROR){
//         std::cout<<"We have an error! "<<place<<" "<<(void* )e<<std::endl;
//     }
// }


A1solution::A1solution() {
    std::cout << "A1Solution created" << std::endl;
}


// Taken from Capsule 2
int A1solution::compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    // compile and link shader program
    // return shader program id
    // ------------------------------------

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}

void A1solution::createRenderingData(unsigned int& VAO, unsigned int& VBO,unsigned int& CBO, unsigned int PBO[], unsigned int& EBO)
{

    // Define and upload geometry to the GPU here ...

    float vertices[] = {
        -0.5f, -0.5f,
        0.5f,  -0.5f,
        0.0f,  0.75f
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2
    };

    float color[] = {
        1.0f,  0.0f, 0.0,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    // 0 - create the vertex array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create the vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 3*2*sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // create the color
    glGenBuffers(1, &CBO);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, 3*3*sizeof(float), color, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(3, PBO);
    // create the triplet of inputs
    int offset = 2;

    for(int i=0;i<3;++i){

        glBindBuffer(GL_ARRAY_BUFFER, PBO[i]);

        float buffer[6];
        for(int j=0;j<3;++j){
            for(int k=0;k<2;++k){
                buffer[2*j+k] = vertices[2*i+k];
            }
        }

        glBufferData(GL_ARRAY_BUFFER, 3*2*sizeof(float), buffer, GL_STATIC_DRAW);

        glVertexAttribPointer(offset+i, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(offset+i);
    }

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}



void A1solution::run(std::string file_name){
    std::cout << "Run run" << std::endl;

    Model model(file_name);
    std::cout << model << std::endl;

    // Initialize GLFW and OpenGL version
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Verify window size
    if (model.windowWidth <= 0 || model.windowHeight <= 0) {
        std::cerr << "Error: Invalid window dimensions from model file!" << std::endl;
        // Fallback so the window at least opens
        model.windowWidth = 800;
        model.windowHeight = 600;
    }
    // Create Window and rendering context using GLFW, resolution is 800x600
    GLFWwindow* window = glfwCreateWindow(model.windowWidth, model.windowHeight, "Comp371 - Assignment 1", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return;
    }

    int basicShaderProgram = compileAndLinkShaders(getBasicVertexShaderSource(), getBasicFragmentShaderSource());

    unsigned int VAO, VBO, CBO, EBO;
    unsigned int PBO[3];
    createRenderingData(VAO, VBO, CBO, PBO, EBO);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(basicShaderProgram);


        // Check for events (keyboard, mouse, window close)
        glfwPollEvents();
        
        // Black background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


        // Swap the buffers (Display the result)
        glfwSwapBuffers(window);
    }

    // Clean up resources when the loop ends
    glfwTerminate();

}