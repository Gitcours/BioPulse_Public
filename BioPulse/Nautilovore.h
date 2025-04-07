#pragma once
#include "Enemy.h"

class Nautilovore :
    public Enemy
{
private:

public:
    Nautilovore(Vector2f _pos, Texture& _text, float _speed, int _hp);

    FloatRect getHitBox() override;
};

