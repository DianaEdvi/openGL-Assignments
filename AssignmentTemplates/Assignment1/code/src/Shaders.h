#ifndef SHADERS_H
#define SHADERS_H

const char* getBasicVertexShaderSource()
{
    return
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;"
    "layout (location = 1) in vec3 col;"
    "out vec3 vertexColor;"
    ""
    "void main()"
    "{"
    "   gl_Position = vec4(aPos, 0, 1);"
    "   vertexColor = col;"
    "}";
}

const char* getBasicFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "in vec3 vertexColor;"
    "out vec3 FragColor;"
    ""
    "void main()"
    "{"
    "   FragColor = vertexColor;"
    "}";
}



#endif