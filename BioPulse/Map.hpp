#pragma once

#include "Outils.h"
#include "Tile.hpp"
#include "Player.h"
#include "TextureManager.h"
#include "EntityManager.h"

class EntityManager;

class Map {
protected:
	int currentMap = 0;
	vector<string> levels = { "Assets/Map/labMap/mapLabSpawn.txt", "Assets/Map/labMap/mapLabRoom1.txt", "Assets/Map/labMap/mapLabRoom2.txt", "Assets/Map/labMap/mapLabBossRoom.txt" };
	vector<bool> levelsColors = { true, false, false, false };
public:
	enum mapSelection {
		LAB_SPAWN = 0,
		LAB_ROOM_1 = 1,
		LAB_ROOM_2 = 2,
		LAB_ROOM_3 = 4,
		LAB_ROOM_4 = 5,
		LAB_BOSS_ROOM = 3,
	};
	void loadLab(vector<shared_ptr<Tile>>& tileMap, Player& player, string path = "Assets/Map/labMap/mapLabSpawn.txt");
	

	int getCurrentMap();
	void setCurrentMap(int value);

	vector<string> getLevels();
	vector<bool> getLevelsColors();
	void setLevels(vector<string> value, vector<bool> colors);
};

extern Map mapReference;
extern vector<shared_ptr<Tile>> tileMap;