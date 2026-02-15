#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>    
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 

struct Model {
        Model(const std::string& file_name);
        glm::mat4 modelView, projection;
        int windowWidth, windowHeight;
        unsigned int numberOfVertices, numberOfTriangles;
        std::vector<glm::vec3> vertices;
        std::vector<unsigned int> indices;
        friend std::ostream &operator<<(std::ostream &out, const Model &model);
};


#endif
