#ifndef TOOL_HPP
#define TOOL_HPP

#include "public_head.hpp"
#include "image.hpp"

//void qll();
void generateGrid(Vertice &Ver, ImageInfomation cam);
void undistort(float& u, float& v,ImageInfomation cam);
void readFile(char** buffer, const char* filePath);
GLuint bindPICToTexture(ImageInfomation cam);
void loadPIC(ImageInfomation *cam, const char* filename);
void parse_json(const char *json_string, SensorConfig *config);
#endif