//
// Created by Victor Puchkarev on 11/4/2024.
//

#ifndef SPLIT_SECOND_GAMESTATE_H
#define SPLIT_SECOND_GAMESTATE_H

#include "Player.h"
#include "Road.h"

#include "graphics/renderer.h"

class GameState {
public:
    explicit GameState(std::unique_ptr<renderer> renderer);

    enum ClickType {
        Click_DOWN = 0,
        Click_MOVE = 1,
        Click_UP = 2,
    };

    void click(float x, float y, ClickType type);
    void update(float dt);
    void render(int width, int height);

    void start_game();

    void reconfigure_camera(int width, int height);
    void draw_game_state(int width, int height);

private:
    std::unique_ptr<renderer> renderer_;
    Player player_;
    Road road_;
    float last_update_;
};

#endif //SPLIT_SECOND_GAMESTATE_H
