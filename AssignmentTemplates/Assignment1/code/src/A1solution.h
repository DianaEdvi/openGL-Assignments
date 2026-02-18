#ifndef  A1SOLUTION_H
#define A1SOLUTION_H

#include <iostream>
#include "Model.h"

class A1solution{
    public: 
        A1solution();
        void run(std::string file_name);
        int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
        void createRenderingData(const Model& model, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
        void renderScene(int shaderProgram, const Model& model, unsigned int& VAO);
    private: 
        std::string fileName;
        int basicMVLoc, basicProjLoc;
};


#endif