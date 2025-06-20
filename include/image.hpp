#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "public_head.hpp"


#define MAX_CAMERAS 10

typedef struct {
    //内参
    char name[50];
    double cx;
    double cy;
    double fx;
    double fy;
    double k1;
    double k2;
    double k3;
    double k4;
    //图像宽高和通道
    int width;
    int height;
    int channels;
    //图像数据
    unsigned char* databuffer;
} ImageInfomation;

typedef struct
{
    //顶点数据和纹理数据
    float* vertices;
    //索引
    int* indices;
    //格子大小
    int gridSize;

}Vertice;


typedef struct 
{
    float output_R[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float output_t[3] = {1, 0, 0};

    const float input_R[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    const float input_t[3] = {0, 0, 0};

}CoordinateInfomation;


typedef struct {
    char calib_type[50];
    int num_cameras;
    ImageInfomation cameras[MAX_CAMERAS];
    CoordinateInfomation Coordinates[4];
} SensorConfig;

#endif