//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_MODEL_H
#define SPLIT_SECOND_MODEL_H

#include <GLES2/gl2.h>
#include <vector>

struct Model {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
};

#endif //SPLIT_SECOND_MODEL_H
