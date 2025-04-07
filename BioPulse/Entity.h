#pragma once
#include "Outils.h"

class Entity
{
protected :
	Vector2f position;
	Texture entityText;
	int health;

public :
	Sprite entitySprite;
	Clock animClock;
	string entityType = "N/A";

	Entity(Vector2f _pos, Texture& text, int _hp);
	void draw(RenderWindow& window);
	virtual FloatRect getHitBox() = 0;

	int getHealth() const;
	void setHealth(int _hp);
};

