#ifndef SHADERS_H
#define SHADERS_H

const char* getBasicVertexShaderSource()
{
    return
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;"
    "uniform mat4 modelview;"
    "uniform mat4 projection;"
    "out vec4 vertexPos;"
    ""
    "void main()"
    "{"
    "   gl_Position = projection * modelview * vec4(aPos, 1);"
    "}";
}

const char* getBasicFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
    "   FragColor = vec4(1.0,1.0,1.0,1.0);"
    "}";
}



#endif