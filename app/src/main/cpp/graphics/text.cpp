//
// Created by Victor Puchkarev on 11/12/24.
//

#include "text.h"

Model text::from_string(const std::string& text) {
    Model final_model {
        .texture = "characters_26_50.png",
    };

    float x_offset = 0.0f;
    for (int ix = 0; ix < text.length(); ++ix) {
        const Model c_model = text::from_character(text.at(ix));
        float new_x_offset = x_offset;
        for (int jx = 0; jx < c_model.vertices.size(); jx += 3) {
            final_model.vertices.push_back(c_model.vertices[jx + 0] + x_offset);
            new_x_offset = fmax(new_x_offset, final_model.vertices.back());
            final_model.vertices.push_back(c_model.vertices[jx + 1]);
            final_model.vertices.push_back(c_model.vertices[jx + 2]);
        }
        x_offset = new_x_offset;

        final_model.normals.insert(final_model.normals.end(),
                                   c_model.normals.begin(),
                                    c_model.normals.end());
        final_model.texcoords.insert(final_model.texcoords.end(),
                                   c_model.texcoords.begin(),
                                   c_model.texcoords.end());
    }

    return final_model;
}

Model text::from_character(char c) {
    constexpr float kCharOffset = 1.0f / 256.0f;
    const float kCharMin = kCharOffset * static_cast<float>(c);
    const float kCharMax = kCharMin + kCharOffset;
    return {
            .vertices {
                    0.0f, 0.0f, 0.0f,  // Bottom left
                    1.0f, 0.0f, 0.0f,  // Bottom right
                    1.0f, 2.0f, 0.0f,  // Top right

                    1.0f, 2.0f, 0.0f,  // Top right
                    0.0f, 2.0f, 0.0f,   // Top left
                    0.0f, 0.0f, 0.0f,  // Bottom left
            },
            .texcoords {
                    kCharMin, 1.0f,  // Bottom left
                    kCharMax, 1.0f,  // Bottom right
                    kCharMax, 0.0f,  // Top right

                    kCharMax, 0.0f,  // Top right
                    kCharMin, 0.0f,   // Top left
                    kCharMin, 1.0f,  // Bottom left
            },
            .texture = "characters_26_50.png",
    };
}