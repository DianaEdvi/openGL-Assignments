#include "A1solution.h"

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

#include "Model.h"

// void debug_gl(int place){
//     GLenum e = glGetError();
//     if(e!=GL_NO_ERROR){
//         std::cout<<"We have an error! "<<place<<" "<<(void* )e<<std::endl;
//     }
// }


A1solution::A1solution() {
    std::cout << "A1Solution created" << std::endl;
}

void A1solution::run(std::string file_name){
    std::cout << "Run run" << std::endl;

    Model model(file_name);
    // std::cout << model << std::endl;

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

    
    while (!glfwWindowShouldClose(window))
    {
        // Check for events (keyboard, mouse, window close)
        glfwPollEvents();
        
        // Black background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the buffers (Display the result)
        glfwSwapBuffers(window);
    }

    // Clean up resources when the loop ends
    glfwTerminate();

}