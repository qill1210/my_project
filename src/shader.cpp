#include "shader.hpp"



Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    //读取着色器文件
    readFile(&VFilebuffer, vertexPath);
    readFile(&FFilebuffer, fragmentPath);

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &VFilebuffer, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &FFilebuffer, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertex);
    glAttachShader(shaderProgramID, fragment);
    glLinkProgram(shaderProgramID);

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);


}

void Shader::use()
{
    glUseProgram(this->shaderProgramID);
}

unsigned int Shader::getShaderID()
{
    return shaderProgramID;
}

Shader::~Shader()
{
    if(shaderProgramID){
        glDeleteProgram(shaderProgramID);
        shaderProgramID = 0;
    }
    delete[] VFilebuffer;
    delete[] FFilebuffer;
}