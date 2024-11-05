//
// Created by ittec on 11/4/2024.
//

#ifndef SPLIT_SECOND_RENDERER_H
#define SPLIT_SECOND_RENDERER_H

#include "model.h"

class renderer {
public:
    renderer();
    ~renderer();

    static int load_texture(const char *filePath);
    void render(const Model& model, int texture) const;

private:
    int program_ = 0;
};


#endif //SPLIT_SECOND_RENDERER_H
