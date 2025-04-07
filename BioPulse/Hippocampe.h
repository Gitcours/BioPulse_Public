#pragma once
#include "Enemy.h"

class Hippocampe :
    public Enemy
{
private :
    Clock shootClock;
	string facing;
    

public:
	bool animPlayed = false;

    Hippocampe(Vector2f _pos, Texture& _text, float _speed, int _hp, string _facing);

    FloatRect getHitBox() override;

    void move() override;
    void pattern(EntityManager* manager) override;
};