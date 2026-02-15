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

    std::cout << model << std::endl;
}