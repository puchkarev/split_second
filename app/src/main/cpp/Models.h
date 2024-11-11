//
// Created by Victor Puchkarev on 11/11/24.
//

#ifndef SPLIT_SECOND_MODELS_H
#define SPLIT_SECOND_MODELS_H

#include "graphics/model.h"

class Models {
public:
    enum BlockType {
        BLOCK_ROAD,
        BLOCK_LEFT_EDGE,
        BLOCK_RIGHT_EDGE,
    };

    static Model PlayerModel(float x, float y, float z);
    static Model BackgroundBlock(float x, float y, float z, BlockType type);
    static Model Axis(float x, float y, float z);
};

#endif //SPLIT_SECOND_MODELS_H