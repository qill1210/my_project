
#define STB_IMAGE_IMPLEMENTATION
#include "tool.hpp"
#include "shader.hpp"
#include "image.hpp"
#include "render.hpp"
#include "public_head.hpp"
#include "process.hpp"


//文件名称数组
string picFile[255] = {"D:/tools/vscode/testcode/project4-pinjie+qujibian/pic/test/front.png", 
                       "D:/tools/vscode/testcode/project4-pinjie+qujibian/pic/test/left.png", 
                       "D:/tools/vscode/testcode/project4-pinjie+qujibian/pic/test/back.png", 
                       "D:/tools/vscode/testcode/project4-pinjie+qujibian/pic/test/right.png"};
int main() {

    //声明
    GLFWwindow* window;
    Vertice Ver;
    Ver.gridSize = 40;
    //存储textureID的数组
    GLuint textureIDs[4];

    //初始化
    if(!Init(window,Ver)){
        return -1;
    }
    //摄像头数据类
    SensorConfig config;
    //着色器类
    Shader shader;

    //处理流程
    render_process(&config, textureIDs, picFile, Ver);
    //渲染类
    Render TEXrender(Ver);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    shader.use();
    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 清空屏幕
        
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用着色器程序
        
        TEXrender.render(shader.getShaderID(),textureIDs,Ver);

        // 交换缓冲区
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理资源
    for (int i = 0; i < 1; i++)
    {
        glDeleteTextures(1, &textureIDs[i]);
        stbi_image_free(config.cameras[i].databuffer);
    }
    glfwTerminate();
    free(Ver.vertices);
    free(Ver.indices);

    return 0;
}