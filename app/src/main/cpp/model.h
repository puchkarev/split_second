//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_MODEL_H
#define SPLIT_SECOND_MODEL_H

#include <GLES2/gl2.h>
#include <vector>

enum BlockType {
    BLOCK_ROAD,
    BLOCK_LEFT_EDGE,
    BLOCK_RIGHT_EDGE,
};

struct Model {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::string texture;

    [[nodiscard]] float SizeX() const;
    [[nodiscard]] float SizeY() const;
    [[nodiscard]] float SizeZ() const;

    static Model PlayerModel(float x, float y, float z);
    static Model BackgroundBlock(float x, float y, float z, BlockType type);
};

#endif //SPLIT_SECOND_MODEL_H
