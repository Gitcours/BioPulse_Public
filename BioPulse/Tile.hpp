#pragma once

#include "Outils.h"
#include "TextureManager.h"

class Tile {
protected:
	shared_ptr<Sprite> sprite = make_shared<Sprite>();
	string type = "BaseTile";
	int layer = 0;
	shared_ptr<Clock> tileClock = make_shared<Clock>();
	float frameTime = 0.1f;
public:
	bool isMoving = false;
	vector<Vector2f> waypoints = { Vector2f(0,0) };
	int currentWaypoint = 0;

	shared_ptr<Sprite> getSprite();
	Tile(Vector2f position);
	string getType();
	void setType(string value);
	int getLayer();
	void setLayer(int value);
	shared_ptr<Clock> getClock();
	float getFrameTime();
};

class Wall : public Tile {
public:
	Wall(Vector2f position);
};

class StickyWall : public Tile {
public:
	StickyWall(Vector2f position);
};

class Door : public Tile {
public:
	Door(Vector2f position);
};

class Floor : public Tile {
public:
	Floor(Vector2f position);
};

class ClimbTile : public Tile {
public:
	ClimbTile(Vector2f position);
};