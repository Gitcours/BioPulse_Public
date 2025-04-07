#pragma once
#include "Entity.h"
class Laser :
    public Entity
{
public :
	Clock delClock;

	Laser(Vector2f _pos, Texture& _text, int _hp);

	FloatRect getHitBox() override;
};

