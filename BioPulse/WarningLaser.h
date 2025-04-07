#pragma once
#include "Entity.h"

class WarningLaser :
    public Entity
{
private :
	bool spawned = false;

public:
	Clock delClock;
	Clock tempClock;
	float wLaserFrame = 0.2f;
	bool shooted = false;

    WarningLaser(Vector2f _pos, Texture& _text, int _hp);

	FloatRect getHitBox() override;

	bool getSpawned() const;
	void setSpawned(bool tOrf);
};

