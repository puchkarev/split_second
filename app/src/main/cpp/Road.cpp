//
// Created by Victor Puchkarev on 11/7/24.
//

#include "Road.h"

#include "Models.h"

#include "graphics/renderer.h"

#include "util/log.h"
#include "util/assert.h"

constexpr float kRoadZ = 0.0f;

Road::Road(float size_x, float size_y, float x_offset, float y_offset) :
    x_position_(x_offset), y_position_(y_offset) {
    const Model block = Models::BackgroundBlock(Models::BLOCK_ROAD);
    block_size_x_ = block.SizeX();
    ASSERT_GT(block_size_x_, 0.0f);
    block_size_y_ = block.SizeY();
    ASSERT_GT(block_size_y_, 0.0f);

    const int blocks_x = static_cast<int>(ceil(size_x / block_size_x_)) - 1;
    const int blocks_y = static_cast<int>(ceil(size_y / block_size_y_));
    for (int y = 0; y < blocks_y; ++y) {
        blocks_.emplace_back();
        for (int x = 0; x < blocks_x; ++x) {
            blocks_.back().emplace_back(
                    x == 0 ? Models::BLOCK_LEFT_EDGE :
                    x + 1 == blocks_x ? Models::BLOCK_RIGHT_EDGE :
                    Models::BLOCK_ROAD);
        }
    }

    LOG_INFO("Generated Road (%f %f) block (%f %f) blocks (%d %d) offset (%f %f)",
             size_x, size_y, block_size_x_, block_size_y_, blocks_x, blocks_y,
             x_position_, y_position_);
}

float Road::length() const {
    return block_size_y_ * static_cast<float>(blocks_.size());
}

float Road::width() const {
    return block_size_x_ * static_cast<float>(blocks_.empty() ? 0 : blocks_.front().size());
}

float Road::width_edge_offset() const {
    return block_size_x_ * 0.5f;
}

void Road::update(float /*dt*/, float /*speed*/) {
    // TODO: Update road graphics as needed
}

void Road::render(renderer& r) const {
    const int count_y = static_cast<int>(blocks_.size());
    const int count_x = static_cast<int>(blocks_.empty() ? 0 : blocks_.front().size());
    float start_x = -block_size_x_ * static_cast<float>(count_x - 1) * 0.5f;
    float start_y = y_position_;

    for (int by = 0; by < count_y; ++by) {
        const float y = start_y + static_cast<float>(by) * block_size_y_;
        for (int bx = 0; bx < count_x; ++bx) {
            const float x = start_x + static_cast<float>(bx) * block_size_x_ + x_position_;
            r.render(Models::BackgroundBlock(blocks_[by][bx]),
                     mat::translate({x, y, kRoadZ}), 1.0);
        }
    }
}
