//
// Created by Adam on 11/20/2021.
//

#ifndef SCAVENGE_GAMEOBJECT_HPP
#define SCAVENGE_GAMEOBJECT_HPP


class GameObject {
protected:
    int posX, posY, height, width, radius;
public:
    void setX(int x);
    void setY(int y);
    void setHeight(int h);
    void setWidth(int w);
    int setRadius(int r);
};


#endif //SCAVENGE_GAMEOBJECT_HPP
