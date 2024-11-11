//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_GRAPHICS_MODEL_H
#define SPLIT_SECOND_GRAPHICS_MODEL_H

#include <vector>

struct Model {
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texcoords;
    std::string texture;

    [[nodiscard]] float SizeX() const;
    [[nodiscard]] float SizeY() const;
    [[nodiscard]] float SizeZ() const;

    static std::vector<float> ComputeNormals(const std::vector<float>& vertices);
};

#endif //SPLIT_SECOND_GRAPHICS_MODEL_H
