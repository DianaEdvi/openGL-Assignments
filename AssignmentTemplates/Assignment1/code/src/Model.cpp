#include "Model.h"

#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

Model::Model(const std::string& file_name){
    std::ifstream file(file_name);

    if (!file.is_open()){
        std::cerr << "File could not be opened!" << std::endl;
        return;
    }

    // Read modelview matrix
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            file >> modelView[i][j];
        }
    }

    // Read projection matrix
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            file >> projection[i][j];
        }
    }

    // Read window size 
    file >> windowWidth;
    file >> windowHeight;

    // Read vertex data 
    file >> numberOfVertices;
    vertices.resize(numberOfVertices);

    for (int i = 0; i < numberOfVertices; i++){
        file >> vertices[i].x >> vertices[i].y >> vertices[i].z;
    }
    
    // Read index data 
    file >> numberOfTriangles;
    indices.resize(numberOfTriangles * 3);

    for (int i = 0; i < numberOfTriangles * 3; i++){
        file >> indices[i];
    }

}

// ------------------------ Output streams ------------------------ 

std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
    return os << glm::to_string(v);
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    os << " ]";
    return os;
}


std::ostream &operator<<(std::ostream &out, const Model &model){
    out << "Modelview: \n" << glm::to_string(model.modelView) << "\n";
    out << "Projection: \n" << glm::to_string(model.projection) << "\n";
    out << "Window width: " << model.windowWidth << "\n";
    out << "Window height: " << model.windowHeight << "\n";
    out << "Number of vertices: " << model.numberOfVertices << "\n";
    out << "Vertices: \n" << model.vertices << "\n";
    out << "Number of triangles: " << model.numberOfTriangles << "\n";
    out << "Indices: \n" << model.indices << std::endl;

    return out;
}
