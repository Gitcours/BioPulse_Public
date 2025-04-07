#include "Tile.hpp"

shared_ptr<Sprite> Tile::getSprite() {
	return sprite;
}

Tile::Tile(Vector2f position) {
	sprite->setTextureRect(IntRect(0, 0, tileRes, tileRes));
	sprite->setPosition(position);
}

string Tile::getType() {
	return type;
}

void Tile::setType(string value) {
	type = value;
}

int Tile::getLayer() {
	return layer;
}

void Tile::setLayer(int value) {
	layer = value;
}

shared_ptr<Clock> Tile::getClock()
{
	return tileClock;
}

float Tile::getFrameTime()
{
	return frameTime;
}

Wall::Wall(Vector2f position) : Tile(position) {
	sprite->setTexture(text.wallTileTexture);
	type = "Wall";
}

StickyWall::StickyWall(Vector2f position) : Tile(position) {
	sprite->setTexture(text.wallStickyTileTexture);
	type = "StickyWallR";
}

Door::Door(Vector2f position) : Tile(position) {
	sprite->setTexture(text.doorTexture);
	type = "Door";
	sprite->setTextureRect(IntRect(0, 0, tileRes, tileRes * 2));
}

Floor::Floor(Vector2f position) : Tile(position)
{
	sprite->setTexture(text.floorTileTexture);
	type = "Floor";
}

ClimbTile::ClimbTile(Vector2f position) : Tile(position) {
	sprite->setTexture(text.climbTileTexture);
	type = "Climb";
}
