#include "render.hpp"

    float vertices1[] = {
        // 位置              // 纹理坐标
        -1.0f, -1.0f, 0.0f,  0.0f, 1.0f,  // 左下角
         1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  // 右下角
         1.0f,  1.0f, 0.0f,  1.0f, 0.0f,  // 右上角
        -1.0f,  1.0f, 0.0f,  0.0f, 0.0f   // 左上角
    };

    // 定义索引数据
    unsigned int indices1[] = {
        0, 1, 2,  // 第一个三角形
        2, 3, 0   // 第二个三角形
    };

const char* OurTextures1[4] = {"ourTexture", 
                            "ourTexture1", 
                            "ourTexture2", 
                            "ourTexture3"};


                            
Render::Render(Vertice Ver)
{
    // 创建 VAO、VBO 和 EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, ((Ver.gridSize+1)*(Ver.gridSize+1)*sizeof(float)*5), Ver.vertices, GL_STATIC_DRAW);    

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (Ver.gridSize*Ver.gridSize*sizeof(int)*6), Ver.indices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 纹理坐标属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Render::render(GLuint shaderProgram,GLuint *textureIDs, Vertice Ver)
{
    
    for (int i = 0; i < 1; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
        glUniform1i(glGetUniformLocation(shaderProgram, OurTextures1[i]), i);
    }
    
    // 绑定 VAO 并绘制
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Ver.gridSize*Ver.gridSize*6, GL_UNSIGNED_INT, 0);

}

Render::~Render()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}