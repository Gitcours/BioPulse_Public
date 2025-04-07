#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Map.hpp"
#include "Entity.h"
#include "Player.h"
#include "TextureManager.h"
#include "EntityManager.h"

#include "UserInput.h"
#include "HUD.h"
#include "Menu.h"
#include "InGameManagement.h"
#include "EditorGrid.hpp"
#include <thread>

extern 	RenderWindow window;

class Game
{
private :
	Font font;
	UserInput input;
	InGameManagement igManage;

	string PlayerName; // Congraulation <PlayerName> ! You are the chosen one!
	Clock volume, MenuSelect,pauseAnim;
	bool doDrawGameWhilePause = true;
	bool isRunning = true;
	Sprite lobby, pentacle;
	RectangleShape lobbyStairs, transitionRect;
	int pagenum = 1000;
	Clock timePassedIGClock;

	//editor UI
	EditorGrid editorGrid;

	Sprite editTilesList;

	Sprite editWallPlain;
	Sprite editWallFloor;
	Sprite editWallSideL;
	Sprite editWallSideR;
	Sprite editWallCeiling;
	Sprite editWallCornerInsideTR;
	Sprite editWallCornerInsideTL;
	Sprite editWallCornerInsideBR;
	Sprite editWallCornerInsideBL;
	Sprite editWallStickyL;
	Sprite editWallStickyR;
	Sprite editWallStickyBL;
	Sprite editWallStickyBR;
	Sprite editWallStickyTL;
	Sprite editWallStickyTR;
	Sprite editPlateformSimple;
	Sprite editPlateformEndL;
	Sprite editPlateformMiddle;
	Sprite editPlateformEndR;

	vector<vector<Sprite*>> editTilesVector;
	map<Sprite*, char> editTileCharMap = { {&editWallPlain, 'w'}, {&editWallFloor, 'M'}, {&editWallSideL, 'H'},
										   {&editWallSideR, 'h'}, {&editWallCeiling, 'c'}, {&editWallCornerInsideTR, 'K'},
		                                   {&editWallCornerInsideTL, 'R'}, {&editWallCornerInsideBR, 'f'}, {&editWallCornerInsideBL, 'g'},
										   {&editWallStickyL, 'J'}, {&editWallStickyR, 'L'}, {&editPlateformSimple, 'T'},
										   {&editPlateformEndL, 'p'}, {&editPlateformMiddle, 'z'}, {&editPlateformEndR, 'q'},
										   {&editWallStickyBL, 'Q'}, {&editWallStickyBR, 'P'}, {&editWallStickyTL, '4'},
		                                   {&editWallStickyTR, '5'} };

	RectangleShape editHoverBox;
	RectangleShape editSelectBox;

	vector<FloatRect> mapFileSelectorBoxes = {};
	vector<string> mapFileSelectorPaths = {};

	shared_ptr<Entity> ePlayer;
	shared_ptr<Player> player;

	shared_ptr<Entity> ePet;
	shared_ptr<Pet> pet;

public : 	
	thread tInGameManage;
	thread tUserInput;
	Game();

	void switchToEditor();

	void displayMenu();
	void displayPause();
	void displayOption();
	void displayCredits();
	void displayStats();
	void displayPlaying();
	void displayEditMenu();
	void displayEdit();
	void display();

	void update();

	void gameLoop();

	void PName(RenderWindow& window, string& name);
	
	void unscale();
};

extern Menu menu;
