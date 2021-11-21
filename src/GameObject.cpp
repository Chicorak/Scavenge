//
// Created by Adam on 11/20/2021.
//

#include "../include/GameObject.hpp"


void GameObject::setX(int x) {
    posX = x;
}

void GameObject::setY(int y) {
    posY = y;
}

void GameObject::setHeight(int h) {
    height = h;
}

void GameObject::setWidth(int w) {
    width = w;
}

void GameObject::setRadius(int r) {
    radius = r;
}

void GameObject::setPosition(int x, int y) {
    GameObject::setX(x);
    GameObject::setY(y);
}

int GameObject::getPositionX() const {
    return GameObject::posX;
}

int GameObject::getPositionY() const {
    return GameObject::posY;
}

void GameObject::setBox(int w, int h) {
    setWidth(w);
    setHeight(h);
}
