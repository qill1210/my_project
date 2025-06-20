#ifndef RENDER_HPP
#define RENDER_HPP

#include "public_head.hpp"
#include "image.hpp"


class Render{

    private:
        unsigned int VAO, VBO, EBO;

    public:
        Render(Vertice Ver);
        void render(GLuint shaderProgram,GLuint *textureIDs, Vertice Ver);
        ~Render();

};


#endif
