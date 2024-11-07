//
// Created by ittec on 11/6/2024.
//

#include "model.h"

Model Model::PlayerModel(float x, float y, float z) {
    return {
            .vertices = {
                    // First triangle
                    x - 0.1f, y - 0.1f, z + 0.0f,  // Bottom left
                    x + 0.1f, y - 0.1f, z + 0.0f,  // Bottom right
                    x + 0.1f,  y + 0.1f, z + 0.0f,  // Top right

                    // Second triangle
                    x + 0.1f,  y + 0.1f, 0.1f,  // Top right
                    x + -0.1f,  y + 0.1f, 0.1f,  // Top left
                    x + -0.1f, y - 0.1f, 0.1f   // Bottom left
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

Model Model::BackgroundModel(float x, float y, float z) {
    return {
            .vertices {
                    x - 1.0f, y - 2.0f, z + 0.0f,  // Bottom left
                    x + 1.0f, y - 2.0f, z+ 0.0f,  // Bottom right
                    x + 1.0f, y + 2.0f, z + 0.0f,  // Top right

                    x + 1.0f, y + 2.0f, 0.0f,  // Top right
                    x - 1.0f, y + 2.0f, 0.0f,   // Top left
                    x - 1.0f, y - 2.0f, 0.0f,  // Bottom left
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
            .texture = "feature_image.png",
    };
}
