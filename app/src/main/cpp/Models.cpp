//
// Created by Victor Puchkarev on 11/11/24.
//

#include "Models.h"

#include "graphics/model.h"

Model Models::PlayerModel() {
    return {
            .vertices = {
                    // First triangle
                    -0.2f, -0.4f, 0.0f,  // Bottom left
                    0.2f, -0.4f, 0.0f,  // Bottom right
                    0.2f, 0.4f, 0.0f,  // Top right

                    // Second triangle
                    0.2f,  0.4f, 0.0f,  // Top right
                    -0.2f, 0.4f, 0.0f,  // Top left
                    -0.2f, -0.4f, 0.0f   // Bottom left
            },
            /*
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
             */
            .texcoords = {
                    // First triangle
                    0.0f, 1.0f,  // Bottom left
                    1.0f, 1.0f,  // Bottom right
                    1.0f, 0.0f,  // Top right

                    1.0f, 0.0f,  // Top right
                    0.0f, 0.0f,   // Top left
                    0.0f, 1.0f,  // Bottom left
            },
            .texture = "car_basic.png",
    };
}

Model Models::BackgroundBlock(BlockType type) {
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
                    -0.25f, -0.25f, 0.0f,  // Bottom left
                    0.25f, -0.25f, 0.0f,  // Bottom right
                    0.25f, 0.25f, 0.0f,  // Top right

                    0.25f, 0.25f, 0.0f,  // Top right
                    -0.25f, 0.25f, 0.0f,   // Top left
                    -0.25f, -0.25f, 0.0f,  // Bottom left
            },
            /*
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
             */
            .texcoords {
                    0.0f, 1.0f,  // Bottom left
                    1.0f, 1.0f,  // Bottom right
                    1.0f, 0.0f,  // Top right

                    1.0f, 0.0f,  // Top right
                    0.0f, 0.0f,   // Top left
                    0.0f, 1.0f,  // Bottom left
            },
            .texture = type_to_texture(type),
    };
}