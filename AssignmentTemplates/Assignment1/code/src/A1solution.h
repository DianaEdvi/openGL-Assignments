#ifndef  A1SOLUTION_H
#define A1SOLUTION_H

#include <iostream>

class A1solution{
    public: 
        A1solution();
        void run(std::string file_name);
        int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
        void createRenderingData(unsigned int& VAO, unsigned int& VBO,unsigned int& CBO, unsigned int PBO[], unsigned int& EBO);
    private: 
        std::string fileName;
};


#endif