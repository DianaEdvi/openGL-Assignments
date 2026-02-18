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
    "in vec3 fragPos;" // position of the pixel
    "in vec3 normal;" // the direction the pixel is facing 
    // material colors 
    "uniform vec3 ambientColor;" // base
    "uniform vec3 diffuseColor;" // angle dependent
    "uniform vec3 specularColor;" // spot
    "uniform float shininessVal;" // material
    "uniform vec3 lightPos;"

    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
    "   vec3 ambient = ambientColor;"

    "   vec3 N = normalize(normal);" // normal
    "   vec3 L = normalize(lightPos - fragPos);" // light direction from pixel to source
    "   vec3 V = normalize(-fragPos);"  // view of the pixel from camera (assumed camera pos = (0,0,0))

    "   float lambertian = max(dot(N,L), 0.0);" // cosine of the angle between them
    "   vec3 diffuse = lambertian * diffuseColor;" // the color of the object depending on the angle 

    "   vec3 specular = vec3(0.0);"
    "   if (lambertian > 0.0){ " // only calc if light is hitting 
    "   vec3 R = reflect(-L, N);" // Law of Reflection, calculates the direction the ray of light bounces off the surface
    "   float specAngle = max(dot(R,V),0.0);" // check if that ray is hitting the camera 
    "   specular = pow(specAngle, shininessVal) * specularColor;" // calculate the shininess (the bigger the shininessVal, the smaller the highlight = shinier)
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