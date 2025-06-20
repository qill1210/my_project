#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "public_head.hpp"
#include "image.hpp"
#include "tool.hpp"

bool Init(GLFWwindow*& window,Vertice &Ver);

void render_process(SensorConfig* config,GLuint* textureIDs, string* picFile, Vertice &Ver);

#endif
