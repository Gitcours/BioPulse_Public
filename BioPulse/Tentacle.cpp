#include "Tentacle.h"

Tentacle::Tentacle(Vector2f _pos, Texture& _text, int _hp, string _type) : tentacleType(_type), Entity(_pos, _text, _hp) 
{ 
	entityType = "Tentacle"; 
	entitySprite.setOrigin(Vector2f(entityText.getSize().y / 2.f, entityText.getSize().y / 2.f));
	entitySprite.setScale(2.f, 2.f);
}

FloatRect Tentacle::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x + boundsSize.x / 7 * 3, boundsPos.y + 0, boundsSize.x / 8, boundsSize.y);
}

string Tentacle::getTentacleType() const { return tentacleType; }
