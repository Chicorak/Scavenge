//
// Created by Adam on 11/20/2021.
//

#ifndef SCAVENGE_PLAYER_HPP
#define SCAVENGE_PLAYER_HPP


#include "GameObject.hpp"
#include <raylib.h>

class player: public GameObject {
protected:
    int ammo, speed, dir;
public:
    void GetInput();
};


#endif //SCAVENGE_PLAYER_HPP
