#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

using namespace std;
using namespace sf;

class Menu
{
private:
	int selected,opselected;
	Font font;
	string name;
	View view;
	Text mainmenu[5];
	Text option[3];
	Text pause[4];
	Text editor[2];
	Sprite binds, sounds, credits,stats,icon;
public:
	Sprite titlescreen, optionscreen, editormenuscreen;
	Sprite pausebgl0, pausebgl1, pausebgl2, silhouette_1, silhouette_2;
	
	Menu(float width, float height);
	void drawMenu(RenderWindow& window);
	void drawPause(RenderWindow& window,Vector2f pos);
	void drawOption(RenderWindow& window);
	void drawEditor(RenderWindow& window);
	void drawBinds(RenderWindow& window);
	void drawSounds(RenderWindow& window);
	void drawCredits(RenderWindow& window);
	void drawStats(RenderWindow& window);
	void moveUp();
	void moveDown();
	void setSelected(int n);
	int pressed() { return selected; }
	View getView();

	void rescale();

	~Menu();
};