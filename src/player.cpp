//
// Created by Adam on 11/20/2021.
//

#include "../include/player.hpp"
#include <raylib.h>


void player::GetInput() {
    if (IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)) player::posX += player::speed;
    if (IsKeyDown(KEY_LEFT)|| IsKeyDown(KEY_A)) player::posX -= player::speed;
    if (IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)) player::posY -= player::speed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) player::posY += player::speed;
}
void player::SetAmmo(int Ammo) {
    player::ammo = Ammo;
}

void player::SetTexture(Texture2D tex) {
    player::CurrentTexture = tex;
}

Texture2D player::GetTexture() {
    return player::CurrentTexture;
}

int player::GetDir() {
    return player::dir;
}

void player::SetDir(int Dir) {
    player::dir = Dir;
}

void player::SetSpeed(int Speed) {
    player::speed = Speed;
}


