//
// Created by puchkarev on 11/7/24.
//

#ifndef SPLIT_SECOND_ROAD_H
#define SPLIT_SECOND_ROAD_H

#include "renderer.h"
#include "model.h"
#include "box2d.h"

class Road {
public:
    Road() : Road(0.0, 0.0, 0.0, 0.0) {}
    Road(float size_x, float size_y, float x_offset, float y_offset);

    [[nodiscard]] box2d box() const;

    void update(float dt, float speed);
    void render(renderer& r) const;

private:
    float x_position_ = 0.0f;
    float y_position_ = 0.0f;
    float block_size_x_ = 0.0f;
    float block_size_y_ = 0.0f;

    std::vector<std::vector<BlockType>> blocks_;

};

#endif //SPLIT_SECOND_ROAD_H
