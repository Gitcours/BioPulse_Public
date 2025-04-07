#pragma once
#include "Entity.h"
#include "Outils.h"

class Projectiles : public Entity
{
private:
	Clock moveclock;
	Clock bulletStartClock;
	float bulletmovdeltaTime;
	float bulletStartDelataTime;
	string direction;

public:
	Projectiles(Vector2f _pos, Texture& _text, string _direction); //Direction = "LEFT" or "RIGHT"
	~Projectiles();
	void update();

	FloatRect getHitBox() override;
};