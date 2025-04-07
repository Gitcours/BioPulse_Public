#pragma once
#include "Enemy.h"

class JellyFishGenerator :
    public Enemy
{
private :
	Clock spawnTime;
	bool spawned = false;

public :
	float jellyFishGenFrame = 0.2f;
	Clock tempClock;

	JellyFishGenerator(Vector2f _pos, Texture& _text, float _speed, int _hp);
	FloatRect getHitBox() override;
	void move() override;
	void pattern(EntityManager* manager) override;

	bool getSpawned() const;
	void setSpawned(bool tOrf) ;
};

