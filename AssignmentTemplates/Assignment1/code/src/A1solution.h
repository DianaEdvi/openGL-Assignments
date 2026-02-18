#ifndef  A1SOLUTION_H
#define A1SOLUTION_H

#include <iostream>
#include "Model.h"

class A1solution{
    public: 
        A1solution();
        void run(std::string file_name);
        int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
        void createRenderingData(const Model& model, unsigned int& VAO, unsigned int& VBO, int& vertexCount);
        void renderScene(int shaderProgram, const Model& model, unsigned int& VAO);
    private: 
        std::string fileName;
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};


#endif