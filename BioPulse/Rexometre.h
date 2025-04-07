#pragma once
#include "Enemy.h"

class Rexometre :
    public Enemy
{
private:

public:
    Rexometre(Vector2f _pos, Texture& _text, float _speed, int _hp);

    FloatRect getHitBox() override;
};

