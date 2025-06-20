#include "process.hpp"

bool Init(GLFWwindow*& window,Vertice &Ver)
{
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 配置 GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    window = glfwCreateWindow(600, 900, "OpenGL Cube", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 初始化 GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    Ver.vertices = (float*)malloc((Ver.gridSize+1)*(Ver.gridSize+1)*sizeof(float)*5);
    Ver.indices = (int*)malloc(Ver.gridSize*Ver.gridSize*sizeof(int)*6);
    return true;
}

void render_process(SensorConfig* config, GLuint* textureIDs, string* picFile,Vertice &Ver)
{
    //加载内参
    char* cam_len_buffer;
    readFile(&cam_len_buffer, "D:/tools/vscode/testcode/project7-pinjie+qujibian+chongtouying/pic/test/camera.json"); 
    
    config->num_cameras = 0;
    parse_json(cam_len_buffer, config);
    
    //计算顶点数据、纹理数据和索引
    generateGrid(Ver, config->cameras[0]);

    cout << "cx  =   "<<config->cameras[0].fy<<endl;

    //将图片数据绑定到纹理
    for (int i = 0; i < 1; i++)
    {
        loadPIC(&config->cameras[i],picFile[i].c_str());
        textureIDs[i] = bindPICToTexture(config->cameras[i]);
    }

    free(cam_len_buffer);
}
