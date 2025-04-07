#pragma once
#include "Entity.h"

class EntityManager;

class Enemy :
    public Entity
{
protected :
    float speed;

public :
    
    Enemy(Vector2f _pos, Texture& _text, float _speed, int _hp);

    virtual FloatRect getHitBox() = 0;
    virtual void move() = 0;
    virtual void pattern(EntityManager* manager) = 0;

    float getSpeed();

};

