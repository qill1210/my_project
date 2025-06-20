#ifndef SHADER_HPP
#define SHADER_HPP

#include "public_head.hpp"
#include "tool.hpp"

class Shader
{
private:
    unsigned int shaderProgramID;
    char* VFilebuffer;
    char* FFilebuffer;
public:
    Shader():Shader("D:/tools/vscode/testcode/project4-pinjie+qujibian/shader/vertex_shader.glsl", 
                  "D:/tools/vscode/testcode/project4-pinjie+qujibian/shader/fragment_shader.glsl"){}
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    unsigned int getShaderID();
    ~Shader();
};




#endif