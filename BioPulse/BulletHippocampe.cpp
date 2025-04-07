#include "BulletHippocampe.h"

BulletHippocampe::BulletHippocampe(Vector2f _pos, Texture& _text, int _hp, float _speed, string _direction) : speed(_speed), direction(_direction), Entity(_pos, _text, _hp)
{
	entityType = "BulletHippo";
}

void BulletHippocampe::move()
{
	if (direction == "RIGHT") 
	{
		entitySprite.move((Vector2f(1.f, 0.f) * speed * timePassed));
	}
	else if (direction == "LEFT")
    {
		entitySprite.move((Vector2f(-1.f, 0.f) * speed * timePassed));
    }
}

FloatRect BulletHippocampe::getHitBox() {
    return entitySprite.getGlobalBounds();
}