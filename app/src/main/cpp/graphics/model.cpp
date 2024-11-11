//
// Created by Victor Puchkarev on 11/6/2024.
//

#include "model.h"

#include "../geometry/vec3d.h"
#include "../util/assert.h"

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

std::vector<float> Model::ComputeNormals(const std::vector<float>& vertices) {
    ASSERT_EQ(vertices.size() % 3, 0);
    std::vector<float> normals;
    for (int i = 0; i < vertices.size(); i += 9) {
        const vec3d a(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
        const vec3d b(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
        const vec3d c(vertices[i + 6], vertices[i + 7], vertices[i + 8]);

        const vec3d e1 = b - a;
        const vec3d e2 = c - a;
        const vec3d n = e1.cross_product(e2);
        for (int j = 0; j < 3; ++j) {
            normals.push_back(n.x());
            normals.push_back(n.y());
            normals.push_back(n.z());
        }
    }
    return normals;
}
