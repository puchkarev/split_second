//
// Created by Victor Puchkarev on 11/11/24.
//

#include "image.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif  // STB_IMAGE_IMPLEMENTATION

#include "../util/log.h"

image::image(unsigned char* raw_data, int len) {
    data_ = stbi_load_from_memory(raw_data, len, &width_, &height_, &channels_, 0);
    if (data_ == nullptr) {
        LOG_ERROR("Failed to load texture image");
    }
}

image::~image() {
    if (data_ != nullptr) {
        stbi_image_free(data_);
    }
}

bool image::valid() const {
    return data() != nullptr;
}

int image::width() const {
    return width_;
}

int image::height() const {
    return height_;
}

int image::channels() const {
    return channels_;
}

unsigned char* image::data() const {
    return data_;
}
