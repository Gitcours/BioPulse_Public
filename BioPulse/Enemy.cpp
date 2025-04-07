#include "Enemy.h"

Enemy::Enemy(Vector2f _pos, Texture& _text, float _speed, int _hp) : speed(_speed), Entity(_pos, _text, _hp)
{
	entitySprite.setOrigin(Vector2f(entityText.getSize().y / 2.f, entityText.getSize().y / 2.f));
}

FloatRect Enemy::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x + boundsSize.x, boundsPos.y + boundsSize.y, boundsSize.x, boundsSize.y);
}

float Enemy::getSpeed() { return speed; }
