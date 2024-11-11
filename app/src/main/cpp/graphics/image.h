//
// Created by Victor Puchkarev on 11/11/24.
//

#ifndef SPLIT_SECOND_GRAPHICS_STB_WRAPPER_H
#define SPLIT_SECOND_GRAPHICS_STB_WRAPPER_H

// simple wrapper around stb_image
class image {
public:
    image(unsigned char* raw_data, int len);
    ~image();

    [[nodiscard]] bool valid() const;
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] int channels() const;
    [[nodiscard]] unsigned char* data() const;

private:
    int width_ = 0;
    int height_ = 0;
    int channels_ = 0;
    unsigned char *data_ = nullptr;
};

#endif //SPLIT_SECOND_GRAPHICS_STB_WRAPPER_H
