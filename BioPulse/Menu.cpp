#include "Menu.h"

Menu::Menu(float width, float height) {
	font.loadFromFile("Assets/Font/pixel.ttf");
	//binds.setTexture(texturemanager->bindsTexture);
	//binds.setPosition(Vector2f(0, 0));
	text.loadTexture();
	float offset = 75;
	icon.setTexture(text.iconTexture);
	icon.setPosition(width / 2 - offset * 6, height / 2 - offset * 4);
	icon.setScale(.5, .8);
	credits.setTexture(text.creditsTexture);
	credits.setScale(1.2, 1.4);
	titlescreen.setOrigin(Vector2f(text.titelscreenTexture.getSize()) / 2.f);
	titlescreen.setPosition(width / 2 - 450, height / 2 - 40);
	//titlescreen.setScale(2.6, 4.75);
	titlescreen.setTexture(text.titelscreenTexture);

	optionscreen.setOrigin(Vector2f(text.optionscreenTexture.getSize()) / 2.f);
	optionscreen.setPosition(width / 2 - 450, height / 2 - 40);
	optionscreen.setScale(2.6, 4.75);
	optionscreen.setTexture(text.optionscreenTexture);

	editormenuscreen.setOrigin(Vector2f(text.editormenuscreenTexture.getSize()) / 2.f);
	editormenuscreen.setPosition(width / 2 - 450, height / 2 - 40);
	editormenuscreen.setScale(2.6, 4.75);

	editormenuscreen.setTexture(text.editormenuscreenTexture);

	pausebgl0.setTexture(text.pausebgl0Texture);
	//pausebgl0.setOrigin(Vector2f(text.optionscreenTexture.getSize()) / 2.f);
	//pausebgl0.setPosition(width / 2 - 1175, height / 2 - 200);
	//pausebgl0.setScale(2.6, 4.75);

	pausebgl1.setTexture(text.pausebgl1Texture);
	pausebgl1.setTextureRect(IntRect(0, 0, text.pausebgl1Texture.getSize().y, text.pausebgl1Texture.getSize().y));
	//pausebgl1.setOrigin(Vector2f(text.optionscreenTexture.getSize()) / 2.f);
	//pausebgl1.setPosition(width / 2 - 1175, height / 2 - 200);
	//pausebgl1.setScale(2.6, 4.75);

	pausebgl2.setTexture(text.pausebgl2Texture);
	////pausebgl2.setOrigin(Vector2f(text.optionscreenTexture.getSize()) / 2.f);
	//pausebgl2.setPosition(width / 2 + offset*5, height / 2);
	pausebgl2.setScale(.05, .05);

	silhouette_1.setTexture(text.silhouette_1Texture);
	silhouette_1.setScale(.05, .05);

	silhouette_2.setTexture(text.silhouette_2Texture);
	silhouette_2.setScale(.05, .05);

	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color{ 117,0,59 });
	mainmenu[0].setString("PLAY");
	mainmenu[0].setCharacterSize(40);
	mainmenu[0].setScale(Vector2f(.75, 1));
	mainmenu[0].setPosition(Vector2f(100, height / (4) + 90));
	mainmenu[0].setScale(Vector2f(.75, 1));
	mainmenu[0].setPosition(Vector2f(100, height / (4) + offset));

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color{ 142,211,74 });
	mainmenu[1].setString("OPTIONS");
	mainmenu[1].setCharacterSize(40);
	mainmenu[1].setScale(Vector2f(.75, 1));
	mainmenu[1].setPosition(Vector2f(100, height / (4) + offset * 2));

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color{ 142,211,74 });
	mainmenu[2].setString("XXXXX");
	mainmenu[2].setCharacterSize(40);
	mainmenu[2].setScale(Vector2f(.75, 1));
	mainmenu[2].setPosition(Vector2f(100, height / (4) + offset * 3));

	mainmenu[3].setFont(font);
	mainmenu[3].setFillColor(Color{ 142,211,74 });
	mainmenu[3].setString("CUSTOM");
	mainmenu[3].setCharacterSize(40);
	mainmenu[3].setScale(Vector2f(.75, 1));
	mainmenu[3].setPosition(Vector2f(100, height / (4) + offset * 4));

	mainmenu[4].setFont(font);
	mainmenu[4].setFillColor(Color{ 142,211,74 });
	mainmenu[4].setString("EXIT");
	mainmenu[4].setCharacterSize(40);
	mainmenu[4].setScale(Vector2f(.75, 1));
	mainmenu[4].setPosition(Vector2f(100, height / (4) + offset * 5));


	option[0].setFont(font);
	option[0].setFillColor(Color{ 142,211,74 });
	option[0].setString("Credits");
	option[0].setCharacterSize(40);
	option[0].setScale(Vector2f(.75, 1));
	option[0].setPosition(Vector2f(100, height / (4) + 110));

	option[1].setFont(font);
	option[1].setFillColor(Color{ 142,211,74 });
	option[1].setString("Controls");
	option[1].setCharacterSize(40);
	option[1].setScale(Vector2f(.75, 1));
	option[1].setPosition(Vector2f(100, height / (4) + 220));

	option[2].setFont(font);
	option[2].setFillColor(Color{ 142,211,74 });
	option[2].setString("Menu");
	option[2].setCharacterSize(40);
	option[2].setScale(Vector2f(.75, 1));
	option[2].setPosition(Vector2f(100, height / (4) + 340));

	pause[0].setFont(font);
	pause[0].setOutlineThickness(-5);
	pause[0].setOutlineColor(Color{ 12,206,148 });
	pause[0].setFillColor(Color{ 117,0,59 });
	pause[0].setString("R    E   S   U   M    E");
	pause[0].setCharacterSize(40);
	pause[0].setScale(Vector2f(.75, 1));
	pause[0].setPosition(Vector2f(50, height / (4) - 125));

	pause[1].setFont(font);
	pause[1].setOutlineThickness(-5);
	pause[1].setOutlineColor(Color{ 12,206,148 });
	pause[1].setFillColor(Color{ 255,255,255 });
	pause[1].setString("S    T   A   T    S");
	pause[1].setCharacterSize(40);
	pause[1].setScale(Vector2f(.75, 1));
	pause[1].setPosition(Vector2f(50, height / (4) - 35));

	pause[2].setFont(font);
	pause[2].setOutlineThickness(-5);
	pause[2].setOutlineColor(Color{ 12,206,148 });
	pause[2].setFillColor(Color{ 255,255,255 });
	pause[2].setString("M    E   N   U");
	pause[2].setCharacterSize(40);
	pause[2].setScale(Vector2f(.75, 1));
	pause[2].setPosition(Vector2f(50, height / (4) + 43));

	pause[3].setFont(font);
	pause[3].setOutlineThickness(-5);
	pause[3].setOutlineColor(Color{ 12,206,148 });
	pause[3].setFillColor(Color{ 255,255,255 });
	pause[3].setString("Q    U   I    T");
	pause[3].setCharacterSize(40);
	pause[3].setScale(Vector2f(.75, 1));
	pause[3].setPosition(Vector2f(50, height / (4) + 130));


	editor[0].setFont(font);
	editor[0].setFillColor(Color{ 142,211,74 });
	editor[0].setString("Menu");
	editor[0].setCharacterSize(40);
	editor[0].setScale(Vector2f(.75, 1));
	editor[0].setPosition(Vector2f(100, height / (4) + offset));

	editor[1].setFont(font);
	editor[1].setFillColor(Color{ 142,211,74 });
	editor[1].setString("New Map");
	editor[1].setCharacterSize(40);
	editor[1].setScale(Vector2f(.75, 1));
	editor[1].setPosition(Vector2f(100, height / (4) + offset*2));

	selected = 0;


}

View Menu::getView() {
	return view;
}



void Menu::rescale() {
	if (titlescreen.getScale() != Vector2f(2.6, 4.75)) {
		titlescreen.setScale(2.6, 4.75);
	}
}

Menu::~Menu() {}

void Menu::setSelected(int n) { selected = n; }

void Menu::drawMenu(RenderWindow& window) {
	window.setView(view);

	window.draw(titlescreen);
	window.draw(icon);
	for (int i = 0; i < 5; i++) {
		window.draw(mainmenu[i]);
	}

}
void Menu::drawPause(RenderWindow& window, Vector2f pos) {

	pausebgl0.setPosition(pos.x - 360, pos.y - 225);
	pausebgl1.setPosition(pos.x - 360, pos.y - 225);
	silhouette_1.setPosition(pos.x + 20, pos.y - 175);
	silhouette_2.setPosition(pos.x + 40, pos.y - 175);
	pausebgl2.setPosition(pos.x, pos.y - 175);


	window.draw(pausebgl0);
	window.draw(pausebgl1);
	window.draw(silhouette_2);
	window.draw(silhouette_1);
	window.draw(pausebgl2);
	window.setView(view);

	for (int i = 0; i < 4; i++) {
		window.draw((pause)[i]);
	}
}
void Menu::drawOption(RenderWindow& window) {
	window.setView(view);
	window.draw(optionscreen);

	for (int i = 0; i < 3; i++) {
		window.draw(option[i]);
	}
}

void Menu::drawEditor(RenderWindow& window) {
	window.setView(view);
	window.draw(editormenuscreen);

	for (int i = 0; i < 2; i++) {
		window.draw(editor[i]);
	}
}

void Menu::drawBinds(RenderWindow& window) {
	window.setView(view);
	window.draw(binds);
}
void Menu::drawSounds(RenderWindow& window) {
	window.setView(view);
	window.draw(credits);
}
void Menu::drawCredits(RenderWindow& window) {
	window.setView(view);
	window.draw(credits);
}

void Menu::drawStats(RenderWindow& window) {
	window.setView(view);
	window.draw(stats);

}

void Menu::moveUp() {

	if (selected - 1 >= -1) {
		if (isMenu)
			mainmenu[selected].setFillColor(Color{ 142,211,74 });
		if (isOption)
			option[selected].setFillColor(Color{ 142,211,74 });
		if (isPause)
			pause[selected].setFillColor(Color{ 255,255,255 });
		if (isEditMenu)
			editor[selected].setFillColor(Color{ 142,211,74 });
		selected--;
		if (selected == -1) {
			if (isMenu) {
				selected = 4;
			}
			if (isOption) {
				selected = 2;
			}
			if (isPause) {
				selected = 3;
			}
			if (isEditMenu) {
				selected = 1;
			}
		}
		if (isMenu)
			mainmenu[selected].setFillColor(Color{ 117,0,59 });
		if (isOption)
			option[selected].setFillColor(Color{ 117,0,59 });
		if (isPause)
			pause[selected].setFillColor(Color{ 117,0,59 });
		if (isEditMenu)
			editor[selected].setFillColor(Color{ 117,0,59 });

	}
	if (selected == 3 and isPause) {
		pause[0].setFillColor(Color{ 255,255,255 });
	}
	if (selected == 1 or selected == 2 and isPause) {
		pause[0].setFillColor(Color{ 255,255,255 });
	}
}

void Menu::moveDown() {
	if (selected + 1 <= 5) {
		if (isMenu)
			mainmenu[selected].setFillColor(Color{ 142,211,74 });
		if (isOption)
			option[selected].setFillColor(Color{ 142,211,74 });
		if (isPause)
			pause[selected].setFillColor(Color{ 255,255,255 });
		if (isEditMenu)
			editor[selected].setFillColor(Color{ 142,211,74 });
		selected++;
		if (selected == 5)
			selected = 0;
		if (isOption) {
			if (selected == 3)
				selected = 0;
		}
		if (isPause) {
			if (selected == 4)
				selected = 0;
		}
		if (isEditMenu) {
			if (selected == 2)
			selected = 0;
		}
		if (isMenu)
			mainmenu[selected].setFillColor(Color{ 117,0,59 });
		if (isOption)
			option[selected].setFillColor(Color{ 117,0,59 });
		if (isPause)
			pause[selected].setFillColor(Color{ 117,0,59 });
		if (isEditMenu)
			editor[selected].setFillColor(Color{ 117,0,59 });
	}
	if (selected == 3 and isPause) {
		pause[0].setFillColor(Color{ 255,255,255 });
	}
}

