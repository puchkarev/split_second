//
// Created by puchkarev on 11/7/24.
//

#include "Road.h"

#include "log.h"

Road::Road(float size_x, float size_y, float y_offset) : y_position_(y_offset) {
    const Model block = Model::BackgroundBlock(0.0, 0.0, 0.0, BLOCK_ROAD);
    block_size_x_ = block.SizeX();
    block_size_y_ = block.SizeY();

    const int blocks_x = static_cast<int>(ceil(size_x / block_size_x_)) - 1;
    const int blocks_y = static_cast<int>(ceil(size_y / block_size_y_));
    for (int y = 0; y < blocks_y; ++y) {
        blocks_.emplace_back();
        for (int x = 0; x < blocks_x; ++x) {
            blocks_.back().emplace_back(
                    x == 0 ? BLOCK_LEFT_EDGE :
                    x + 1 == blocks_x ? BLOCK_RIGHT_EDGE :
                    BLOCK_ROAD);
        }
    }

    LOG_INFO("Generated Road (%f %f) block (%f %f) blocks (%d %d) offset %f",
             size_x, size_y, block_size_x_, block_size_y_, blocks_x, blocks_y,
             y_position_);
}

box2d Road::box() const {
    return {
        0.0,
        -y_position_,
        block_size_x_ * static_cast<float>(blocks_.front().size()),
        block_size_y_ * static_cast<float>(blocks_.size()),
    };
}

void Road::update(float dt, float speed) {
    y_position_ += dt * speed;
}

void Road::render(renderer& r) const {
    const int count_y = static_cast<int>(blocks_.size());
    const int count_x = static_cast<int>(blocks_.front().size());
    float start_x = -block_size_x_ * static_cast<float>(count_x - 1) * 0.5f;
    float start_y = -block_size_y_ * static_cast<float>(count_y - 1) * 0.5f - y_position_;

    const float z = 0.0f;
    for (int by = 0; by < count_y; ++by) {
        const float y = start_y + static_cast<float>(by) * block_size_y_;
        for (int bx = 0; bx < count_x; ++bx) {
            const float x = start_x + static_cast<float>(bx) * block_size_x_;
            r.render(Model::BackgroundBlock(x, y, z, blocks_[by][bx]));
        }
    }
}
