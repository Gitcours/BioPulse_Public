#include "JellyFishGenerator.h"
#include "EntityManager.h"
#include "TextureManager.h"

JellyFishGenerator::JellyFishGenerator(Vector2f _pos, Texture& _text, float _speed, int _hp) : Enemy(_pos, _text, _speed, _hp) 
{ 
	entityType = "JellyFishGenerator"; 
	entitySprite.setOrigin(Vector2f(entityText.getSize().y / 2.f, entityText.getSize().y / 2.f));
	entitySprite.setScale(2.f, 2.f);
}

FloatRect JellyFishGenerator::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x + boundsSize.x / 7 * 3, boundsPos.y, boundsSize.x / 8, boundsSize.y);
}

void JellyFishGenerator::move()
{}

void JellyFishGenerator::pattern(EntityManager* manager) 
{
	if (spawnTime.getElapsedTime().asSeconds() >= 2.f)
	{
		spawnTime.restart();
		manager->createMiniMeduse(Vector2f(entitySprite.getPosition().x, entitySprite.getPosition().y - entitySprite.getGlobalBounds().height / 2 + 10), text.miniMText, 150.f, 2);
	}
}

bool JellyFishGenerator::getSpawned() const { return spawned; }
void JellyFishGenerator::setSpawned(bool tOrf) { spawned = tOrf; }