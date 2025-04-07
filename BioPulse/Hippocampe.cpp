#include "Hippocampe.h"
#include "TextureManager.h"
#include "EntityManager.h"

Hippocampe::Hippocampe(Vector2f _pos, Texture& _text, float _speed, int _hp, string _facing) : facing(_facing), Enemy(_pos, _text, _speed, _hp){
	entityType = "Hippocampe";
	if (facing == "LEFT") {
		entitySprite.setScale(-1, 1);
	}
	else if (facing == "RIGHT")
    {
		entitySprite.setScale(1, 1);
	}
}

FloatRect Hippocampe::getHitBox()
{
    Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
    Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
    return FloatRect(boundsPos.x + boundsSize.x / 3.f, boundsPos.y + 0, boundsSize.x / 3.f, boundsSize.y);
}

void Hippocampe::pattern(EntityManager* manager) 
{
	if (shootClock.getElapsedTime().asSeconds() > 1.5f && !animPlayed) {
		animPlayed = true;
	}
    if (shootClock.getElapsedTime().asSeconds() > 2.5f) {
		manager->createBulletHippocampe(entitySprite.getPosition() - Vector2f(10, 16), text.bulletTexture, 1, 125.f, facing);
		animPlayed = false;
        shootClock.restart();
    }
}

void Hippocampe::move() {}