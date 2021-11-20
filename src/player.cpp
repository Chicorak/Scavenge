//
// Created by Adam on 11/20/2021.
//

#include "../include/player.hpp"

void player::GetInput() {
    if (IsKeyDown(KEY_RIGHT)) player::posX += 2.0f;
    if (IsKeyDown(KEY_LEFT)) player::posX -= 2.0f;
    if (IsKeyDown(KEY_UP)) player::posY -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) player::posY += 2.0f;
}
