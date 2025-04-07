#include "WarningLaser.h"

WarningLaser::WarningLaser(Vector2f _pos, Texture& _text, int _hp) : Entity(_pos, _text, _hp) 
{ 
	entityType = "WarningLaser"; 
	entitySprite.setScale(2.f, 2.f);
}

FloatRect WarningLaser::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x, boundsPos.y, boundsSize.x, boundsSize.y);
}

bool WarningLaser::getSpawned() const { return spawned; }
void WarningLaser::setSpawned(bool tOrf) { spawned = tOrf; }