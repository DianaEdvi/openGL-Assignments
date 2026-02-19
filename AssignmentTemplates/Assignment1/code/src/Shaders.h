#ifndef SHADERS_H
#define SHADERS_H

const char* getVertexShaderSource()
{
    return
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;"
    "layout (location = 1) in vec3 aNormal;"
    "layout (location = 2) in vec3 aFaceNormal;"
    "layout (location = 3) in vec3 aBarycentric;"
    "uniform mat4 modelview;"
    "uniform mat4 projection;"
    
    "out vec3 fragPos;"
    "out vec3 normal;"
    "flat out vec3 flatNormal;"
    "out vec3 barycentric;"
    ""
    "void main()"
    "{"
        "barycentric = aBarycentric;"
        "vec4 viewPos = modelview * vec4(aPos, 1);"
        "fragPos = viewPos.xyz;"
        "mat3 normalMat = transpose(inverse(mat3(modelview)));"
        "normal = normalize(mat3(normalMat) * aNormal);"
        "flatNormal = normalize(normalMat * aFaceNormal);"
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
    "uniform vec3 ambientColor = vec3(0.1f, 0.05f, 0.05f);" // base
    "uniform vec3 diffuseColor = vec3(1.0f, 0.5f, 0.5f);" // angle dependent
    "uniform vec3 specularColor = vec3(0.3f, 0.3f, 0.3f);" // spot
    "uniform float shininessVal = 5.0f;" // material
    "uniform vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);"

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

// Same as Phong, with a few changes
const char* getFlatFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "in vec3 fragPos;" 
    "flat in vec3 flatNormal;" // The direction the face is facing 
    // material colors 
    "uniform vec3 ambientColor = vec3(0.1f, 0.05f, 0.05f);"
    "uniform vec3 diffuseColor = vec3(1.0f, 0.5f, 0.5f);"
    "uniform vec3 specularColor = vec3(0.3f, 0.3f, 0.3f);" 
    "uniform float shininessVal = 5.0f;"
    "uniform vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);"

    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
    "   vec3 ambient = ambientColor;"

    "   vec3 N = normalize(flatNormal);" // face normal
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

const char* getCircleFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
    "   FragColor = vec4(1.0,1.0,0.0,0.0);"
    "}";
}

const char* getVoronoiFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "in vec3 fragPos;"
    "in vec3 barycentric;" 
    "in vec3 normal;"
    "uniform vec3 ambientColor = vec3(0.1f, 0.05f, 0.05f);"
    "uniform vec3 specularColor = vec3(0.3f, 0.3f, 0.3f);" 
    "uniform float shininessVal = 5.0f;"
    "uniform vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);"
    
    "out vec4 FragColor;"
    ""
    "void main()"
    "{"
        "vec3 diffuseColor = vec3(1.0f, 0.5f, 0.5f);"
        "float p1 = barycentric.x;"
        "float p2 = barycentric.y;"
        "float p3 = barycentric.z;"

        "vec3 ambient = ambientColor;"

        "vec3 N = normalize(normal);"
        "vec3 L = normalize(lightPos - fragPos);" 
        "vec3 V = normalize(-fragPos);"  

        "float lambertian = max(dot(N,L), 0.0);" 

        // check which coordinate is biggest and assign diffuse color to that
        "if (p1 > p2 && p1 > p3){"
        "diffuseColor = vec3(1.0f, 0.5f, 0.5f);"
        "}"
        "else if (p2 > p3){"
        "diffuseColor = vec3(0.5f, 1.0f, 0.5f);"
        "}"
        "else {"
        "diffuseColor = vec3(0.5f, 0.5f, 1.0f);"
        "}"
        "vec3 diffuse = lambertian * diffuseColor;" 

        "vec3 specular = vec3(0.0);"
        "if (lambertian > 0.0){ "  
        "vec3 R = reflect(-L, N);" 
        "float specAngle = max(dot(R,V),0.0);" 
        "specular = pow(specAngle, shininessVal) * specularColor;" 
    "}"
        "FragColor = vec4(ambient + diffuse + specular,1.0);"
    "}";
}


#endif