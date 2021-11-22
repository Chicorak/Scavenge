//
// Created by Adam on 11/20/2021.
//

#ifndef SCAVENGE_PLAYER_HPP
#define SCAVENGE_PLAYER_HPP


#include "GameObject.hpp"
#include <raylib.h>

class player: public GameObject {
protected:
    int ammo, dir, speed;
    Texture2D CurrentTexture;
public:
    bool GetInput();
    void SetAmmo(int Ammo);
    void SetDir(int Dir);
    void SetTexture(Texture2D tex);
    void SetSpeed(int Speed);
    int GetDir();
    int GetAmmo() const;
    Texture2D GetTexture();
};


#endif //SCAVENGE_PLAYER_HPP
