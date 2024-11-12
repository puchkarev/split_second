//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_GRAPHICS_GL_ASSIST_H
#define SPLIT_SECOND_GRAPHICS_GL_ASSIST_H

#include <vector>

uint createProgram();
void deleteProgram(uint program);
uint loadTexture(int width, int height, int channels, unsigned char* data);

void startNewRender();
void configureCamera(uint program, const float* mvp, bool row_major);
void renderModelUsingProgram(uint program,
                             const std::vector<float>& vertices,
                             const std::vector<float>& normals,
                             const std::vector<float>& texcoords,
                             uint texture, float alpha);

#endif //SPLIT_SECOND_GRAPHICS_GL_ASSIST_H
