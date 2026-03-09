#ifndef  A2SOLUTION_H
#define A2SOLUTION_H

#include <iostream>
#include "Model.h"

class A2solution{
    public: 
        A2solution();
        void run(std::string file_name);
        int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
        void createRenderingData(const Model& model, unsigned int& VAO, unsigned int& VBO, int& vertexCount);
        void assignUniforms(int shaderProgram, const Model& model, unsigned int& VAO);
    private: 
        std::string fileName;
        void pickTriangle(const Model& model, const glm::vec3 screenCoords, int width, int height);
        glm::vec3 calculateBarycentricWeights(const glm::vec3& P, const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
};  

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 faceNormal;
    glm::vec3 barycentric;
    glm::vec3 inCenterWorld;
    float inRadius;
};


#endif