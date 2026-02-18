#include "A1solution.h"

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

#include "Model.h"
#include "Shaders.h"

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

void A1solution::createRenderingData(const Model& model, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    
    // 0 - create the vertex array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create the vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, model.numberOfVertices * sizeof(glm::vec3), &model.vertices[0], GL_STATIC_DRAW);

    // Attribute pointer: Location 0 = position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), &model.indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

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

    int shaderProgram;
    int basicShaderProgram = compileAndLinkShaders(getBasicVertexShaderSource(), getBasicFragmentShaderSource());

    unsigned int VAO, VBO, CBO, EBO;
    unsigned int PBO[3];
    createRenderingData(model, VAO, VBO, EBO);

    // For shader swapping 
    int counter = 0;
    bool wasSDown = false;

    while (!glfwWindowShouldClose(window))
    {
        // Black background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(basicShaderProgram);
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        int mvLocation = glGetUniformLocation(basicShaderProgram, "modelview");
        int projLocation = glGetUniformLocation(basicShaderProgram, "projection");

        glUniformMatrix4fv(mvLocation, 1, GL_FALSE, &model.modelView[0][0]);
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, &model.projection[0][0]);


        glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, 0);

        // Check for events (keyboard, mouse, window close)
        glfwPollEvents();

        // Swap the buffers (Display the result)
        glfwSwapBuffers(window);

        bool isSDown = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
        
        // only reassign once per click
        if (isSDown && !wasSDown){
            counter++;
            switch (counter % 4)
            {
            case 0:
                std::cout << "Phong shader program" << std::endl;
                break;
            case 1:
                std::cout << "Voronoi shader program" << std::endl;
                break;
            case 2:
                std::cout << "Flat shader program" << std::endl;
                break;
            case 3:
                std::cout << "Circle shader program" << std::endl;        
            default:
                break;
            }
        }

        wasSDown = isSDown;
    }

    // Clean up resources when the loop ends
    glfwTerminate();

}