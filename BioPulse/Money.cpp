#include "Money.h"

Money::Money(Vector2f _pos, Texture& _text, int _hp) : Entity(_pos, _text, _hp)
{
	entitySprite.setOrigin(Vector2f(entityText.getSize().x / 2.f, entityText.getSize().y / 2.f));
	entityType = "Money";
	entitySprite.setScale(.5, .5);
}

FloatRect Money::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x, boundsPos.y, boundsSize.x, boundsSize.y);
}
