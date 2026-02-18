#ifndef SHADERS_H
#define SHADERS_H

const char* getVertexShaderSource()
{
    return
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;"
    "layout (location = 1) in vec3 aNormal;"
    "uniform mat4 modelview;"
    "uniform mat4 projection;"
    
    "out vec3 fragPos;"
    "out vec3 normal;"
    ""
    "void main()"
    "{"
        "vec4 viewPos = modelview * vec4(aPos, 1);"
        "fragPos = viewPos.xyz;"
        "mat3 normalMat = transpose(inverse(mat3(modelview)));"
        "normal = normalize(mat3(normalMat) * aNormal);"
    "   gl_Position = projection * viewPos;"
    "   "
    "}";
}

const char* getPhongFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "in vec3 fragPos;"
    "in vec3 normal;"
    // material colors 
    "uniform vec3 ambientColor;"
    "uniform vec3 diffuseColor;"
    "uniform vec3 specularColor;"
    "uniform float shininessVal;"
    "uniform vec3 lightPos;"

    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
    "   vec3 ambient = ambientColor;"

    "   vec3 N = normalize(normal);"
    "   vec3 L = normalize(lightPos - fragPos);"
    "   vec3 V = normalize(-fragPos);"  

    "   float lambertian = max(dot(N,L), 0.0);"
    "   vec3 diffuse = lambertian * diffuseColor;"

    "   vec3 specular = vec3(0.0);"
    "   if (lambertian > 0.0){ "
    "   vec3 R = reflect(-L, N);"
    "   float specAngle = max(dot(R,V),0.0);"
    "   specular = pow(specAngle, shininessVal) * specularColor;"
    "}"
    "   FragColor = vec4(ambient + diffuse + specular,1.0);"
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