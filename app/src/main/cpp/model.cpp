//
// Created by ittec on 11/6/2024.
//

#include "model.h"

float Model::SizeX() const {
    float min_ = vertices[0];
    float max_ = vertices[0];
    for (int ix = 0; ix < vertices.size(); ix += 3) {
        min_ = fmin(min_, vertices[ix]);
        max_ = fmax(max_, vertices[ix]);
    }
    return max_ - min_;
}

float Model::SizeY() const {
    float min_ = vertices[1];
    float max_ = vertices[1];
    for (int ix = 1; ix < vertices.size(); ix += 3) {
        min_ = fmin(min_, vertices[ix]);
        max_ = fmax(max_, vertices[ix]);
    }
    return max_ - min_;
}

float Model::SizeZ() const {
    float min_ = vertices[2];
    float max_ = vertices[2];
    for (int ix = 2; ix < vertices.size(); ix += 3) {
        min_ = fmin(min_, vertices[ix]);
        max_ = fmax(max_, vertices[ix]);
    }
    return max_ - min_;
}

Model Model::PlayerModel(float x, float y, float z) {
    return {
            .vertices = {
                    // First triangle
                    x - 0.2f, y - 0.3f, z + 0.0f,  // Bottom left
                    x + 0.2f, y - 0.3f, z + 0.0f,  // Bottom right
                    x + 0.2f,  y + 0.3f, z + 0.0f,  // Top right

                    // Second triangle
                    x + 0.2f,  y + 0.3f, z + 0.0f,  // Top right
                    x + -0.2f,  y + 0.3f, z + 0.0f,  // Top left
                    x + -0.2f, y - 0.3f, z + 0.0f   // Bottom left
            },
            .normals = {
                    // First triangle
                    0.0f, 0.0f, 1.0f,  // Bottom left
                    0.0f, 0.0f, 1.0f,  // Bottom right
                    0.0f, 0.0f, 1.0f,  // Top right

                    // Second triangle
                    0.0f, 0.0f, 1.0f,  // Top right
                    0.0f, 0.0f, 1.0f,  // Top left
                    0.0f, 0.0f, 1.0f   // Bottom left
            },
            .texcoords = {
                    // First triangle
                    0.0f, 1.0f,  // Bottom left (green)
                    0.0f, 1.0f,  // Bottom right (green)
                    0.0f, 1.0f,  // Top right (green)

                    // Second triangle
                    0.0f, 1.0f,  // Top right (green)
                    0.0f, 1.0f,  // Top left (green)
                    0.0f, 1.0f   // Bottom left (green)
            },
            // .texture = "block_blue.png",
    };
}

Model Model::BackgroundBlock(float x, float y, float z, BlockType type) {
    auto type_to_texture = [](BlockType type) -> std::string {
        switch (type) {
            case BLOCK_ROAD:
                return "block_road.png";
            case BLOCK_LEFT_EDGE:
                return "block_road_edge_left.png";
            case BLOCK_RIGHT_EDGE:
                return "block_road_edge_right.png";
        }
    };

    return {
            .vertices {
                    x - 0.25f, y - 0.25f, z + 0.0f,  // Bottom left
                    x + 0.25f, y - 0.25f, z+ 0.0f,  // Bottom right
                    x + 0.25f, y + 0.25f, z + 0.0f,  // Top right

                    x + 0.25f, y + 0.25f, z + 0.0f,  // Top right
                    x - 0.25f, y + 0.25f, z + 0.0f,   // Top left
                    x - 0.25f, y - 0.25f, z + 0.0f,  // Bottom left
            },
            .normals = {
                    // First triangle
                    0.0f, 0.0f, 1.0f,  // Bottom left
                    0.0f, 0.0f, 1.0f,  // Bottom right
                    0.0f, 0.0f, 1.0f,  // Top right

                    // Second triangle
                    0.0f, 0.0f, 1.0f,  // Top right
                    0.0f, 0.0f, 1.0f,  // Top left
                    0.0f, 0.0f, 1.0f   // Bottom left
            },
            .texcoords {
                    0.0f, 2.0f,  // Bottom left
                    1.0f, 2.0f,  // Bottom right
                    1.0f, 0.0f,  // Top right

                    1.0f, 0.0f,  // Top right
                    0.0f, 0.0f,   // Top left
                    0.0f, 2.0f,  // Bottom left
            },
            .texture = type_to_texture(type),
    };
}
