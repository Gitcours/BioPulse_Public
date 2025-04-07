#pragma once
#include "Outils.h"
#include "TextureManager.h"

class HUD
{
private:	

public:
	Clock animClock,healClock;

	vector<Sprite> playerHP = {};
	vector<Sprite> monnaieCountTotal = {};
	Sprite monnaie, monnaieCount0, monnaieCount1, monnaieCount2, monnaieCount3, monnaieCount4,
		monnaieCount5, monnaieCount6, monnaieCount7, monnaieCount8, monnaieCount9;
	Sprite  playerIcon;
	HUD();
	bool isAnimDone=true;
	void createPlayerHP(int);
	void addPlayerHP(int=1);
	void addPlayerMoney(int);
	void updateMoney(int);
	void drawHUD(RenderWindow& window,Vector2f pos);
	void drawIcon(RenderWindow& window, Vector2f pos);
	void drawPlayerHP(RenderWindow& window, Vector2f pos);
	void drawMoney(RenderWindow& window, Vector2f pos);
	vector<Sprite> getPlayerHP() const;	
};

