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

}

std::ostream &operator<<(std::ostream &out, const Model &model){
    out << "Modelview: \n" << glm::to_string(model.modelView);
    return out;
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