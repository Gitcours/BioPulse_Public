#pragma once
#include "Entity.h"

class Money :
    public Entity
{
private :

public :
    Money(Vector2f _pos, Texture& _text, int _hp);

	FloatRect getHitBox() override;
};

