#pragma once
#include "Enemy.h"
#include "player.h"
class Crabe : public Enemy
{
public:
    Crabe(Vector2f _pos, Texture& _text, float _speed, int _hp, int w1, int w2);

    FloatRect getHitBox() override;
    void move() override; 
    void pattern(EntityManager* manager) override;

private:
    int waypoint1;
    int waypoint2;

    bool movingRight;  
};
