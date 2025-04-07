#include "Laser.h"

Laser::Laser(Vector2f _pos, Texture& _text, int _hp) : Entity(_pos, _text, _hp) 
{ 
	entityType = "Laser"; 
	entitySprite.setScale(2.f, 1.f);
}

FloatRect Laser::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x, boundsPos.y + boundsSize.y / 41.f * 18.5f, boundsSize.x, boundsSize.y / 41.f);
}
