#ifndef SHADERS_H
#define SHADERS_H

const char* getVertexShaderSource()
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

const char* getPhongFragmentShaderSource()
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

const char* getFlatFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
    "   FragColor = vec4(1.0,1.0,0.0,1.0);"
    "}";
}

const char* getCircleFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
    "   FragColor = vec4(0.0,1.0,1.0,1.0);"
    "}";
}

const char* getVoronoiFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
    "   FragColor = vec4(1.0,0.0,1.0,1.0);"
    "}";
}


#endif