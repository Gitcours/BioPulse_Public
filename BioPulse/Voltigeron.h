#pragma once
#include "Enemy.h"

class Voltigeron :
    public Enemy
{
private :

public :
    Voltigeron(Vector2f _pos, Texture& _text, float _speed, int _hp);

    FloatRect getHitBox() override;
};

