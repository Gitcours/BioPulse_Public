#include "Rexometre.h"

Rexometre::Rexometre(Vector2f _pos, Texture& _text, float _speed, int _hp) : Enemy(_pos, _text,_speed, _hp)
{}

FloatRect Rexometre::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x + boundsSize.x / 3.f, boundsPos.y + boundsSize.y / 3.f, boundsSize.x / 3.f, boundsSize.y / 8.f * 5);
}
