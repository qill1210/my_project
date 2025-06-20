#include "tool.hpp"


void Coordinate_Mapping(){


}

#if 1
//去畸变函数
void undistort(float& u, float& v,ImageInfomation cam) {
    
    // 将纹理坐标转换为图像坐标
    float x = u * cam.width;
    float y = v * cam.height;

    // 归一化图像坐标
    float xn = (x - cam.cx)/cam.fx;
    float yn = (y - cam.cy)/cam.fy;

    // 计算径向畸变
    float r1 = sqrt(xn * xn + yn * yn);
    float theta  = atan(r1);
    float theta2 = theta * theta;
    float theta4 = theta2 * theta2;
    float theta6 = theta4 * theta2;
    float theta8 = theta6 * theta2;
    float theta_d = theta * (1 + cam.k1 * theta2 + cam.k2 * theta4 + cam.k3 * theta6 + cam.k4 * theta8);
    
    float scale = (r1 > 1e-8)? theta_d / r1 : 1.0f;
    //printf("qll----%f\n",theta);

    // 计算去畸变后的归一化图像坐标
    float xd = xn * scale;
    float yd = yn * scale;
    
    //半畸变
    float S = 1;
    float xd1 = S*xd + (1-S)*xn;
    float yd1 = S*yd + (1-S)*yn;

    // 转换回纹理坐标
    u = (xd1 * cam.fx + cam.cx) / cam.width;
    v = (yd1 * cam.fy + cam.cy) / cam.height;
}
#endif


#if 1
void generateGrid(Vertice &Ver, ImageInfomation cam)
{
    int flag = 1;
	int cont = 0;
	// 生成顶点数据
    for (int y = 0; y <= Ver.gridSize; ++y) {
        for (int x = 0; x <= Ver.gridSize; ++x) {
            Ver.vertices[cont] = -1.0f + x * 2.0f / Ver.gridSize;
            Ver.vertices[cont + 1] = -1.0f + y * 2.0f / Ver.gridSize;
			Ver.vertices[cont + 2] = 0;
            Ver.vertices[cont + 3] = (float)x / Ver.gridSize;
            Ver.vertices[cont + 4] = 1 - (float)y / Ver.gridSize;
            if (flag == 1){
                float u = Ver.vertices[cont + 3];
                float v = Ver.vertices[cont + 4];
                undistort(u, v,cam);
                Ver.vertices[cont + 3] = u;
                Ver.vertices[cont + 4] = v;                
            }else{
#if 0
                //a. 根据输出camera的内参，将每个顶点坐标映射到输出camera的相机坐标系
                float image_x = vertices[cont + 3]* width;
                float image_y = vertices[cont + 4]* height;
                float camera_x = (image_x - cx) / fx;
                float camera_y = (image_y - cy) / fy;
                float camera_z = 1.0;

                //计算角度的旋转
                rotation(output_R,angle_deg);
                
                // c. 根据输出相机的外参，将相机坐标系的点经过旋转平移映射到统一的世界坐标系
                float world_x = output_R[0][0] * camera_x + output_R[0][1] * camera_y + output_R[0][2] * camera_z + output_t[0];
                float world_y = output_R[1][0] * camera_x + output_R[1][1] * camera_y + output_R[1][2] * camera_z + output_t[1];
                float world_z = output_R[2][0] * camera_x + output_R[2][1] * camera_y + output_R[2][2] * camera_z + output_t[2];

                // d. 根据输入相机的外参，将世界坐标系的点经过旋转平移映射到输入相机的相机坐标系
                float input_camera_x = input_R[0][0] * (world_x - input_t[0]) + input_R[0][1] * (world_y - input_t[1]) + input_R[0][2] * (world_z - input_t[2]);
                float input_camera_y = input_R[1][0] * (world_x - input_t[0]) + input_R[1][1] * (world_y - input_t[1]) + input_R[1][2] * (world_z - input_t[2]);
                float input_camera_z = input_R[2][0] * (world_x - input_t[0]) + input_R[2][1] * (world_y - input_t[1]) + input_R[2][2] * (world_z - input_t[2]);

                // e. 根据输入相机的内参，将相机坐标系的点畸变映射到输入相机的图像坐标系-纹理坐标系
                float normalized_x = input_camera_x / input_camera_z;
                float normalized_y = input_camera_y / input_camera_z;

                float r1 = sqrt(normalized_x * normalized_x + normalized_y * normalized_y);
                float theta  = atan(r1);
                float theta2 = theta * theta;
                float theta4 = theta2 * theta2;
                float theta6 = theta4 * theta2;
                float theta8 = theta6 * theta2;
                float theta_d = theta * (1 + k1 * theta2 + k2 * theta4 + k3 * theta6 + k4 * theta8);
                float scale = (r1 > 1e-8)? theta_d / r1 : 1.0f;
                float distorted_x = normalized_x * scale;
                float distorted_y = normalized_y * scale;
                float texture_x = distorted_x * fx + cx;
                float texture_y = distorted_y * fy + cy;

                // 将纹理坐标转换为[0, 1]范围
                texture_x /= width;
                texture_y /= height;
                vertices[cont + 3] = texture_x;
                vertices[cont + 4] = texture_y;
#endif
           }

            cont+=5;
        }
    }
	
	// 生成索引数据，按照
	//* * * * *
	//*     * *
	//*   *   *
	//* *     *
	//* * * * *
	cont = 0;
    for (int y = 0; y < Ver.gridSize; ++y) {
        for (int x = 0; x < Ver.gridSize; ++x) {
			unsigned int bottomLeft = y * (Ver.gridSize + 1) + x;
            unsigned int bottomRight = bottomLeft + 1;
            unsigned int topLeft = (y + 1) * (Ver.gridSize + 1) + x;
            unsigned int topRight = topLeft + 1;
         
            Ver.indices[cont] = bottomLeft;
			Ver.indices[cont+1] = bottomRight;
			Ver.indices[cont+2] = topRight;
			Ver.indices[cont+3] = topRight;
			Ver.indices[cont+4] = topLeft;
			Ver.indices[cont+5] = bottomLeft;
			cont+=6;
        }
	}
	
	
};

#endif

// 从文件中读取内容函数
void readFile(char** buffer, const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("ERROR::SHADER::FILE_NOT_FOUND: %s\n", filePath);
        
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    //*buffer = (char*)malloc(size);
    *buffer = new char[size];
    if (*buffer == NULL) {
        printf("ERROR::SHADER::MEMORY_ALLOCATION_FAILED\n");
        fclose(file);
        
    }

    fread(*buffer, 1, size, file);
    fclose(file);

}

GLuint bindPICToTexture(ImageInfomation cam){
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // 设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //上传纹理参数

    if(cam.channels == 3){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cam.width, cam.height, 0, GL_RGB, GL_UNSIGNED_BYTE, cam.databuffer);
    } else if(cam.channels == 4){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cam.width, cam.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cam.databuffer);
    }

    return textureID;
}

void loadPIC(ImageInfomation *cam, const char* filename) {
    //int width, height, channels;
    cam->databuffer = stbi_load(filename, &cam->width, &cam->height, &cam->channels, 0);
    if (!cam->databuffer) {
        printf("Failed to load image: %s\n", filename);
        exit(1);
    }

    printf("Image loaded: %dx%d, %d channels\n", cam->width, cam->height, cam->channels);
}

// 解析 JSON 数据
void parse_json(const char *json_string, SensorConfig *config) {
    cJSON *root = cJSON_Parse(json_string);
    if (!root) {
        fprintf(stderr, "Failed to parse JSON\n");
        return;
    }

    cJSON *sensor_config = cJSON_GetObjectItem(root, "sensor_config");
    if (sensor_config) {
        cJSON *calib_type = cJSON_GetObjectItem(sensor_config, "calib_type");
        if (calib_type && cJSON_IsString(calib_type)) {
            strncpy(config->calib_type, calib_type->valuestring, 50);
        }

        cJSON *cam_param = cJSON_GetObjectItem(sensor_config, "cam_param");
        if (cam_param && cJSON_IsArray(cam_param)) {
            int num_cameras = cJSON_GetArraySize(cam_param);
            config->num_cameras = num_cameras > MAX_CAMERAS ? MAX_CAMERAS : num_cameras;

            for (int i = 0; i < config->num_cameras; i++) {
                cJSON *camera = cJSON_GetArrayItem(cam_param, i);
                if (camera) {
                    cJSON *name = cJSON_GetObjectItem(camera, "name");
                    cJSON *cx = cJSON_GetObjectItem(camera, "cx");
                    cJSON *cy = cJSON_GetObjectItem(camera, "cy");
                    cJSON *fx = cJSON_GetObjectItem(camera, "fx");
                    cJSON *fy = cJSON_GetObjectItem(camera, "fy");
                    cJSON *k1 = cJSON_GetObjectItem(camera, "k1");
                    cJSON *k2 = cJSON_GetObjectItem(camera, "k2");
                    cJSON *k3 = cJSON_GetObjectItem(camera, "k3");
                    cJSON *k4 = cJSON_GetObjectItem(camera, "k4");
                    cJSON *width = cJSON_GetObjectItem(camera, "width");
                    cJSON *height = cJSON_GetObjectItem(camera, "height");

                    if (name && cJSON_IsString(name)) {
                        strncpy(config->cameras[i].name, name->valuestring, 50);
                    }
                    if (cx && cJSON_IsNumber(cx)) {
                        config->cameras[i].cx = cx->valuedouble;
                    }
                    if (cy && cJSON_IsNumber(cy)) {
                        config->cameras[i].cy = cy->valuedouble;
                    }
                    if (fx && cJSON_IsNumber(fx)) {
                        config->cameras[i].fx = fx->valuedouble;
                    }
                    if (fy && cJSON_IsNumber(fy)) {
                        config->cameras[i].fy = fy->valuedouble;
                    }
                    if (k1 && cJSON_IsNumber(k1)) {
                        config->cameras[i].k1 = k1->valuedouble;
                    }
                    if (k2 && cJSON_IsNumber(k2)) {
                        config->cameras[i].k2 = k2->valuedouble;
                    }
                    if (k3 && cJSON_IsNumber(k3)) {
                        config->cameras[i].k3 = k3->valuedouble;
                    }
                    if (k4 && cJSON_IsNumber(k4)) {
                        config->cameras[i].k4 = k4->valuedouble;
                    }
                    if (width && cJSON_IsNumber(width)) {
                        config->cameras[i].width = width->valueint;
                    }
                    if (height && cJSON_IsNumber(height)) {
                        config->cameras[i].height = height->valueint;
                    }
                }
            }
        }
    }

    cJSON_Delete(root);  // 释放 cJSON 对象
}
