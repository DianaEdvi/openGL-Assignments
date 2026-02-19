// COMP 371 Assignment 1
// Written by Diana Edvi (40198139)

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

void A1solution::createRenderingData(const Model& model, unsigned int& VAO, unsigned int& VBO, int& vertexCount)
{
    // Represents each vertex's normal, where the normal is the sum of the normals of all of the faces that touch it
    // The indices used for indexing in this array access the same vertices as in the vertices array
    std::vector<glm::vec3> summedNormals(model.numberOfVertices, glm::vec3(0.0f));

    // Loop through indices, and for each triangle, add the normal of the triangle face to each of its indice
    // By the end, every 
    for (size_t i = 0; i < model.indices.size(); i += 3) {
        // Get the indices of the triangle 
        unsigned int i0 = model.indices[i];
        unsigned int i1 = model.indices[i+1];
        unsigned int i2 = model.indices[i+2];

        // Get the vertices of the triangle based on indices 
        glm::vec3 p0 = model.vertices[i0];
        glm::vec3 p1 = model.vertices[i1];
        glm::vec3 p2 = model.vertices[i2];

        // Calculate Face Normal
        glm::vec3 edge1 = p1 - p0;
        glm::vec3 edge2 = p2 - p0;
        glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2)); 

        // Add this normal to all vertices that share this face
        summedNormals[i0] += faceNormal;
        summedNormals[i1] += faceNormal;
        summedNormals[i2] += faceNormal;
    }

    std::vector<Vertex> bufferData;

    // loop through every triangle, 3 indices at a time
    for (int i = 0; i < model.indices.size(); i += 3){
        // get indices
        unsigned int i0 = model.indices[i];
        unsigned int i1 = model.indices[i + 1];
        unsigned int i2 = model.indices[i + 2];
        
        // get positions 
        // must normalize because they are probably not 1
        glm::vec3 n0 = glm::normalize(summedNormals[i0]);
        glm::vec3 n1 = glm::normalize(summedNormals[i1]);
        glm::vec3 n2 = glm::normalize(summedNormals[i2]);
        
        glm::vec3 p0 = model.vertices[i0];
        glm::vec3 p1 = model.vertices[i1];
        glm::vec3 p2 = model.vertices[i2];
        
        // Calculate Face Normal
        glm::vec3 edge1 = p1 - p0;
        glm::vec3 edge2 = p2 - p0;
        glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));

        // Assign barycentric coords
        glm::vec3 b0 = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 b1 = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 b2 = glm::vec3(0.0f, 0.0f, 1.0f);

        // populate the buffer 
        bufferData.push_back({model.vertices[i0], n0, faceNormal, b0});
        bufferData.push_back({model.vertices[i1], n1, faceNormal, b1});
        bufferData.push_back({model.vertices[i2], n2, faceNormal, b2});
    }
    
    vertexCount = bufferData.size();

    // create the vertex array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create the vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), &bufferData[0], GL_STATIC_DRAW);

    // Attribute pointer: Location 0 = position 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Attribute pointer: Location 1 = normal 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    
    // Attribute pointer: Location 2 = face normal 
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, faceNormal));
    glEnableVertexAttribArray(2);

    // Attribute pointer: Location 3 = barycentric 
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, barycentric));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

// Pass in variables to gpu 
void A1solution::assignUniforms(int shaderProgram, const Model& model, unsigned int& VAO){
        
    glBindVertexArray(VAO);

    int mvLocation = glGetUniformLocation(shaderProgram, "modelview");
    int projLocation = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(mvLocation, 1, GL_FALSE, &model.modelView[0][0]);
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, &model.projection[0][0]);
}


void A1solution::run(std::string file_name){
    Model model(file_name);

    // Initialize GLFW and OpenGL version
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create Window and rendering context using GLFW
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

    glEnable(GL_DEPTH_TEST);

    // Compile and link shaders
    int shaderProgram;
    int phongShaderProgram = compileAndLinkShaders(getVertexShaderSource(), getPhongFragmentShaderSource());
    int flatShaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFlatFragmentShaderSource());
    int circleShaderProgram = compileAndLinkShaders(getVertexShaderSource(), getCircleFragmentShaderSource());
    int voronoiShaderProgram = compileAndLinkShaders(getVertexShaderSource(), getVoronoiFragmentShaderSource());

    shaderProgram = phongShaderProgram;

    unsigned int VAO, VBO;
    int vertexCount = 0;
    createRenderingData(model, VAO, VBO, vertexCount);

    // For shader swapping and mode swapping
    int counter = 0;
    bool wasSDown = false;
    bool wasWDown = false;
    bool isWireframe = false;

    while (!glfwWindowShouldClose(window))
    {
        // Black background
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        assignUniforms(shaderProgram, model, VAO);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        // Check for events (keyboard, mouse, window close)
        glfwPollEvents();

        // Swap the buffers (display the result)
        glfwSwapBuffers(window);

        bool isSDown = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
        bool isWDown = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        
        // switch shader programs
        if (isSDown && !wasSDown){
            counter++;
            switch (counter % 4)
            {
                case 0:
                std::cout << "Phong shader program" << std::endl;
                shaderProgram = phongShaderProgram;
                break;
                case 1:
                std::cout << "Flat shader program" << std::endl;
                shaderProgram = flatShaderProgram;
                break;
                case 2:
                std::cout << "Circle shader program" << std::endl;
                shaderProgram = circleShaderProgram;
                break;
                case 3:
                std::cout << "Voronoi shader program" << std::endl;
                shaderProgram = voronoiShaderProgram;        
                default:
                break;
            }
        }
        
        // switch mode
        if (isWDown && !wasWDown){
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                if (!isWireframe){
                    std::cout << "Wireframe mode" << std::endl;
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    isWireframe = true;
                }
                else {
                    std::cout << "Shader mode" << std::endl;
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    isWireframe = false;
                }
            }
        }

        wasSDown = isSDown;
        wasWDown = isWDown;
    }

    // Clean up resources when the loop ends
    glfwTerminate();

}