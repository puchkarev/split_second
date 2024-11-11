//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_GRAPHICS_MODEL_H
#define SPLIT_SECOND_GRAPHICS_MODEL_H

#include <GLES2/gl2.h>
#include <vector>

struct Model {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::string texture;

    [[nodiscard]] float SizeX() const;
    [[nodiscard]] float SizeY() const;
    [[nodiscard]] float SizeZ() const;

    static std::vector<GLfloat> ComputeNormals(const std::vector<GLfloat>& vertices);
};

#endif //SPLIT_SECOND_GRAPHICS_MODEL_H
