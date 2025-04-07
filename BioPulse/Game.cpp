#include "Game.h"

UserInput input;
InGameManagement igManage;

Event event;
/*-------------------------------------*\
|   page num        *   fun             |
| --------------------------------------|
|       1000        *   MainMenu        |
|       2000        *   PauseMenu       |
|       -1          *   close           |
|        0          *   GameFirstLaunch |
|        1          *   options         |
|        2          *   credits(?)      |
|        3          *   Play            |
|        4          *   Sounds          |
|        5          *   Controls/Binds  |
|        6          *   Stats           |
|        13         *   Editor Menu     |
\*-------------------------------------*/
Menu menu(1920, 1080);
HUD hud;

const int lineSize = 60;
int xSize = 60, ySize = 60;
char tileSelected = '-';

string createMapDirectory(int number = 1) {
	string path = "Assets/Map/customMaps/newMap_" + to_string(number);
	if (create_directory(path)) { return path; }
	else { return createMapDirectory(number + 1); }
}
string createLevelFile(string directory, int number = 1) {
	string path = directory + "/newLevel_" + to_string(number) + ".txt";
	if (ofstream(path)) { return path; }
	else { return createLevelFile(directory, number + 1); }
}


Game::Game() : isRunning(true) {
	font.loadFromFile("Assets/Font/pixel.ttf");

	text.loadTexture();
	//////////////////////////////////////////////////////////////////////////
	window.setVerticalSyncEnabled(true);
	window.setIcon(text.icon.getSize().x, text.icon.getSize().y, text.icon.getPixelsPtr());

	manager->createPlayer(Vector2f(0, 0), text.idlePlayerLeftText, text.jumpEffectPlayerText, text.landEffectPlayerText, 450.f, 15);
	manager->createPet(Vector2f(0, 0), text.petIdleText);

	ePlayer = manager->getAllPlayers()[0];
	player = dynamic_pointer_cast<Player>(ePlayer);

	ePet = manager->getAllPets()[0];
	pet = dynamic_pointer_cast<Pet>(ePet);


	hud.createPlayerHP(player->getHealth());

	mapReference.loadLab(tileMap, *player, "Assets/Map/labMap/mapLabSpawn.txt");

	//////////////////////////////////////////////////////////////////////////
	thread tInGameManage(&InGameManagement::igManagement, igManage, manager, ref(text), player, &hud);
	thread tUserInput(&UserInput::userInputManagement, input, manager, ref(text), player);


	tInGameManage.detach();
	tUserInput.detach();

	editTilesList.setTexture(text.editTilesListTexture);

	editWallPlain.setTexture(text.wallPlainTileTexture);
	editWallFloor.setTexture(text.wallFloorTileTexture);
	editWallSideL.setTexture(text.wallTileTexture);
	editWallSideR.setTexture(text.wallTileTexture); editWallSideR.setOrigin(tileRes, 0); editWallSideR.setScale(-1, 1);
	editWallCeiling.setTexture(text.wallCeilingTexture);
	editWallCornerInsideTR.setTexture(text.wallCornerInsideTileTexture);
	editWallCornerInsideTL.setTexture(text.wallCornerInsideTileTexture); editWallCornerInsideTL.setOrigin(tileRes, 0); editWallCornerInsideTL.setScale(-1, 1);
	editWallCornerInsideBR.setTexture(text.wallCornerInsideTileTexture); editWallCornerInsideBR.setOrigin(0, tileRes); editWallCornerInsideBR.setScale(1, -1);
	editWallCornerInsideBL.setTexture(text.wallCornerInsideTileTexture); editWallCornerInsideBL.setOrigin(tileRes, tileRes); editWallCornerInsideBL.setScale(-1, -1);

	editWallStickyL.setTexture(text.wallStickyTileTexture);
	editWallStickyR.setTexture(text.wallStickyTileTexture); editWallStickyR.setOrigin(tileRes, 0); editWallStickyR.setScale(-1, 1);
	editWallStickyBL.setTexture(text.wallStickyBottomTileTexture);
	editWallStickyBR.setTexture(text.wallStickyBottomTileTexture); editWallStickyBR.setOrigin(tileRes, 0); editWallStickyBR.setScale(-1, 1);
	editWallStickyTL.setTexture(text.wallStickyBottomTileTexture); editWallStickyBR.setOrigin(0, tileRes); editWallStickyBR.setScale(1, -1);
	editWallStickyTR.setTexture(text.wallStickyBottomTileTexture); editWallStickyTR.setOrigin(tileRes, tileRes); editWallStickyTR.setScale(-1, -1);

	editPlateformSimple.setTexture(text.floorTileTexture);
	editPlateformEndL.setTexture(text.floorEndTileTexture);
	editPlateformMiddle.setTexture(text.floorMiddleTileTexture);
	editPlateformEndR.setTexture(text.floorEndTileTexture); editPlateformEndR.setOrigin(tileRes, 0); editPlateformEndR.setScale(-1, 1);

	editTilesVector.push_back( vector({ &editWallPlain, &editWallFloor, &editWallSideL, &editWallSideR, &editWallCeiling }) );
	editTilesVector.push_back( vector({ &editWallCornerInsideTR, &editWallCornerInsideTL, &editWallCornerInsideBR, &editWallCornerInsideBL }) );
	editTilesVector.push_back( vector({ &editWallStickyL, &editWallStickyR }) );
	editTilesVector.push_back(vector({ &editWallStickyBL, &editWallStickyBR, &editWallStickyTL, &editWallStickyTR }));
	editTilesVector.push_back(vector( { &editPlateformSimple, &editPlateformEndL, &editPlateformMiddle, &editPlateformEndR }) );

	editHoverBox.setFillColor(Color(255, 255, 255, 80));
	editSelectBox.setFillColor(Color(255, 50, 50, 80));
}

void Game::switchToEditor() {

	isMenu = false;
	isEditMenu = false;
	isEditing = true;

	string newMapPath = createMapDirectory();
	string newLevelPath = createLevelFile(newMapPath);
	fstream mapStream(newLevelPath);
	char line[lineSize + 1];
	for (int i = 0; i < lineSize; i++) {
		line[i] = '-';
	}
	line[lineSize] = '\n';
	for (int i = 0; i < lineSize; i++) {
		mapStream.write(line, lineSize + 1);
	}
	mapStream.write(";", 1);
	mapStream.flush();

	mapReference.setLevels({ newLevelPath }, { false });
	mapReference.setCurrentMap(0);
	mapReference.loadLab(tileMap, *player, newLevelPath);

	editorGrid = EditorGrid(lineSize, lineSize);
	player->entitySprite.setPosition(lineSize * tileRes / 2, lineSize * tileRes / 2);
	player->getCamera()->setCenter(lineSize * tileRes / 2, lineSize * tileRes / 2);

	player->getCamera()->setSize(1920 / 1.7f, 1080 / 1.7f);

	/*for (const auto& entry : directory_iterator("Assets/Map/customMaps"))
	{
		cout << entry.path() << endl;
	}*/
}

void Game::displayMenu() {

	if (isMenu) {
		menu.drawMenu(window);
	}
	window.display();
}

void Game::displayPause() {
	if (isPause) {
		//displayPlaying();
		menu.drawPause(window, Vector2f(player->entitySprite.getPosition().x, player->entitySprite.getPosition().y));
	}
	window.display();

}

void Game::displayOption() {
	if (isOption and !isControls and !isSounds) {
		menu.drawOption(window);
	}
	if (isControls) {
		menu.drawBinds(window);
	}
	if (isSounds) {
		menu.drawSounds(window);
	}
	window.display();
}

void Game::displayCredits() {
	if (isCredits) {
		menu.drawCredits(window);
	}
	window.display();
}

void Game::displayStats() {
	if (isStats) {
		menu.drawStats(window);
	}
	window.display();
}
void Game::displayPlaying() {
	////if (isPlaying) {
	if (mapReference.getCurrentMap() == Map::LAB_SPAWN) {
		player->getCamera()->setSize(1920 / 3.f, 1080 / 3.f);
	}else if (mapReference.getCurrentMap() == Map::LAB_ROOM_1){
		player->getCamera()->setSize(1920 / 1.5f, 1080 / 1.5f);
	}else if (mapReference.getCurrentMap() == Map::LAB_ROOM_2){
		player->getCamera()->setSize(1920 / 1.5f, 1080 / 1.5f);
	}else if (mapReference.getCurrentMap() == Map::LAB_ROOM_3){
		player->getCamera()->setSize(1920 / 1.5f, 1080 / 1.5f);
	}else if (mapReference.getCurrentMap() == Map::LAB_ROOM_4){
		player->getCamera()->setSize(1920 / 1.5f, 1080 / 1.5f);
	}else if (mapReference.getCurrentMap() == Map::LAB_BOSS_ROOM){
		player->getCamera()->setSize(1920 / 1.5f, 1080 / 1.5f);
	}
	//player->getCamera()->setSize(1920 / 1.5f, 1080 / 1.5f);

	window.setView(*player->getCamera());

	//window.setView(window.getDefaultView());


	for (shared_ptr<Tile> tile : tileMap) {
		if (tile) {
			//if (tile->getLayer() == 0) {
			window.draw(*tile->getSprite());
			//}
		}
	}

	managerMutex.lock();

	if (pet->showDialogue) {
		window.draw(pet->dialogueBoxSprite);
		window.draw(pet->petDialogue);
	}

	if (!pet->petisaplatform || pet->petIsGoingToPlatform)
	{
		pet->draw(window);
	}

	window.draw(player->entitySprite);
	window.draw(player->playerJumpEffectSprite);
	window.draw(player->playerLandEffectSprite);

	if (pet->petisaplatform && !pet->petIsGoingToPlatform)
	{
		pet->draw(window);
	}

	for (shared_ptr<Entity> entity : manager->getAllEntities()) {
		if (entity->entityType != "Player" && entity->entityType != "Pet") {
			entity->draw(window);
		}
	}
	hud.drawHUD(window, Vector2f(player->entitySprite.getPosition().x, player->entitySprite.getPosition().y));

	managerMutex.unlock();
	//hitbox
	/*RectangleShape hitbox(player->getHitBox().getSize());
	hitbox.setPosition(player->getHitBox().getPosition());
	hitbox.setFillColor(Color(0, 255, 255, 100));
	window.draw(hitbox);*/
	//hitbox
	if (!isPause) {
		window.display();
	}
}

void Game::displayEditMenu() {
	if (isEditMenu) {
		menu.drawEditor(window);
		mapFileSelectorBoxes.clear();
		mapFileSelectorPaths.clear();
		float yOffset = 0;
		float xOffset = 0;
		FloatRect viewRect(menu.getView().getViewport().getPosition().x, menu.getView().getViewport().getPosition().y, menu.getView().getSize().x, menu.getView().getSize().y);
		for (const auto& entry : directory_iterator("Assets/Map/customMaps"))
		{
			Text directoryName;
			string path = entry.path().filename().string();
			directoryName.setString(entry.path().filename().string());
			directoryName.setFont(font);
			directoryName.setFillColor(Color{ 142,211,74 });

			directoryName.setPosition(menu.getView().getCenter() + Vector2f(-1 * (menu.getView().getSize().x / 13.f * 6.f), 50) + Vector2f(xOffset, yOffset));
			if (!(viewRect.contains(directoryName.getGlobalBounds().getPosition().x + directoryName.getGlobalBounds().getSize().x, menu.getView().getCenter().y))) {
				yOffset += 120;
				xOffset = 0;
				directoryName.setPosition(menu.getView().getCenter() + Vector2f(-1 * (menu.getView().getSize().x / 13.f * 6.f), 50) + Vector2f(xOffset, yOffset));
			}
			xOffset += directoryName.getGlobalBounds().getSize().x + 40;

			window.draw(directoryName);
			mapFileSelectorBoxes.push_back(directoryName.getGlobalBounds());
			mapFileSelectorPaths.push_back(entry.path().string());
		}

		Vector2i mouseWorldPos = Vector2i(window.mapPixelToCoords(Mouse::getPosition(window)));
		for (int i = 0; i < mapFileSelectorBoxes.size(); i++) {
			FloatRect rect = mapFileSelectorBoxes[i];
			if (rect.contains(Vector2f(mouseWorldPos))) {
				RectangleShape hoverRect;
				hoverRect.setPosition(rect.getPosition());
				hoverRect.setSize(Vector2f(rect.getSize().x, 44));
				hoverRect.setFillColor(Color(255, 255, 255, 80));
				window.draw(hoverRect);
			}
		}
	}
	window.display();
}

void Game::displayEdit() {
	if (isEditing) {
		window.setView(*player->getCamera());
		Vector2f camPos = player->getCamera()->getCenter();
		Vector2f camSize = player->getCamera()->getSize();

		for (shared_ptr<Tile> tile : tileMap) {
			if (tile) {
				//if (tile->getLayer() == 0) {
				window.draw(*tile->getSprite());
				//}
			}
		}
		editorGrid.draw();

		//tile list position
		editTilesList.setPosition(camPos + Vector2f(camSize.x / 10.f * 3, camSize.y / -2.f));

		//tile list scaling
		float scaleRatio = camSize.y / text.editTilesListTexture.getSize().y;
		editTilesList.setScale(Vector2f(scaleRatio, scaleRatio));

		//tile list drawing
		window.draw(editTilesList);

		//tiles in list
		for (int i = 0; i < editTilesVector.size(); i++) {
			vector<Sprite*> vect = editTilesVector[i];
			for (int k = 0; k < vect.size(); k++) {
				Sprite* tile = vect[k];
				Vector2f basePos = editTilesList.getPosition();
				Vector2f baseSize = editTilesList.getGlobalBounds().getSize();
				tile->setPosition(basePos.x + baseSize.x / 8.f + (baseSize.x / 6.5f * k), basePos.y + baseSize.y / 6.f + (baseSize.x / 6.5f * i));

				tile->setScale(scaleRatio / 2.f * (tile->getScale().x / abs(tile->getScale().x)), scaleRatio / 2.f * (tile->getScale().y / abs(tile->getScale().y)));

				window.draw(*tile);
			}
		}
		Vector2f mouseWorldPos = window.mapPixelToCoords(Mouse::getPosition(window));
		for (int i = 0; i < editTilesVector.size(); i++) {
			vector<Sprite*> vect = editTilesVector[i];
			for (int k = 0; k < vect.size(); k++) {
				Sprite* tile = vect[k];
				if (tile->getGlobalBounds().contains(mouseWorldPos)) {
					editHoverBox.setPosition(tile->getPosition());
					editHoverBox.setSize(tile->getGlobalBounds().getSize());
					i = editTilesVector.size();
					break;
				}
				else {
					editHoverBox.setSize(Vector2f(0, 0));
				}
			}
		}
		char value = tileSelected;
		FloatRect newSelectBox(0, 0, 0, 0);
		for_each(editTileCharMap.begin(), editTileCharMap.end(),
			[&value, &newSelectBox](const pair<Sprite*, char>& p)
			{
				if (p.second == value)
				{
					newSelectBox = (p.first)->getGlobalBounds();
				}
			});
		editSelectBox.setPosition(newSelectBox.getPosition());
		editSelectBox.setSize(newSelectBox.getSize());

		window.draw(editHoverBox);
		window.draw(editSelectBox);

		
		Sprite previewTile;
		for_each(editTileCharMap.begin(), editTileCharMap.end(),
			[&value, &previewTile](const pair<Sprite*, char>& p)
			{
				if (p.second == value)
				{
					previewTile.setTexture(*p.first->getTexture());
				}
			});
		previewTile.setPosition(Vector2f(Vector2i(mouseWorldPos / float(tileRes)) * tileRes));
		previewTile.setColor(Color(255, 255, 255, 100));
		if (!(editTilesList.getGlobalBounds().intersects(previewTile.getGlobalBounds()))) {
			window.draw(previewTile);
		}
		
		window.display();
	}
}


void Game::display() {
	window.clear();

	if (isOption) {
		displayOption();
	}
	if (isMenu) {
		displayMenu();
	}
	else if (isPlaying)
	{
		displayPlaying();
	}
	if (isEditMenu) {
		displayEditMenu();
	}
	if (isEditing)
	{
		displayEdit();
	}
	if (isPause and !isOption) {
		displayPlaying();

		window.setView(*player->getCamera());
		if (doDrawGameWhilePause) {
			displayPlaying();
			doDrawGameWhilePause = false;
		}
		displayPause();
	}
	if (isStats) {
		displayStats();
	}
}


void Game::update() {

	anim.continueAnimation(hud.playerIcon);
	if (Joystick::isConnected(0) && !isConnected)
	{
		isConnected = true;
	}
	if (!isRunning) {
		window.close();
	}
	if (isPlaying) {
		isMenu = false;
		isOption = false;
		isSounds = false;
	}
	if (isOption) {
		isPlaying = false;
	}
	if (isStats) { isPause = false; }
	if (isPause) {
		isMenu = false;
		isOption = false;
	}
	if (isEditMenu) {
		isMenu = false;
	}
	if (isCredits) {
		isMenu = false;
	}
	timePassedIG = timePassedIGClock.restart().asSeconds();
	if (isPlaying) {
		//cout << isUpdateHP;
		//if (isUpdateHP)
		//{
		//	cout << player->getHealth();
		//	isUpdateHP = false;
		//}
		//hud.createPlayerHP(player->getHealth());
		//hud.addPlayerMoney(player->getMoney());
		//cout << player->getMoney();
		//cout << player->getHealth();
		/*if (player->getMoney() >= 10) {
			player->setMoney(0);
			player->setHealth(player->getHealth() + 1);
			hud.addPlayerHP();
			isUpdateHP = true;
			if (isUpdateHP) {
				for (int i = 0; i < 6; i++) {
					if (hud.animClock.getElapsedTime().asSeconds() > 0.1)
					{
						anim.continueAnimation(hud.playerHP.front());
					}
				}
				isUpdateHP = false;

			}
			cout << player->getHealth();
		}*/
	}
	if (Keyboard::isKeyPressed(Keyboard::Return) or Joystick::isButtonPressed(0, 0)) {

		if (MenuSelect.getElapsedTime().asSeconds() > .300) {
			if (menu.pressed() == 0 and isMenu and isFirstStart) {
				pagenum = 0;
			}
			else if (menu.pressed() == 0 and isMenu and !isFirstStart) {
				pagenum = 3;
			}if (menu.pressed() == 0 and isPause) {
				pagenum = 3;
			}if (menu.pressed() == 1 and isMenu) {
				pagenum = 1;
				menu.moveUp();
			}if (menu.pressed() == 2 and isMenu) {
				pagenum = 2;
			}if (menu.pressed() == 3 and isMenu) {
				pagenum = 13;
				menu.moveUp();
				menu.moveUp();
				menu.moveUp();
			}if (menu.pressed() == 4 and isMenu) {
				pagenum = -1;
			}if (menu.pressed() == 0 and isOption and !isControls and !isSounds) {
				pagenum = 4;
			}if (menu.pressed() == 1 and isOption and !isControls and !isSounds) {
				pagenum = 5;
			}if (menu.pressed() == 2 and isOption and !isControls and !isSounds) {
				pagenum = 1000;
				menu.moveUp();
				menu.moveUp();
			}if (menu.pressed() == 0 and isPause) {
				pagenum = 3;
			}if (menu.pressed() == 1 and isPause) {
				pagenum = 6;
			}if (menu.pressed() == 2 and isPause) {
				pagenum = 1;
			}if (menu.pressed() == 3 and isPause) {
				pagenum = -1;
			}if (menu.pressed() == 0 and isEditMenu) {
				pagenum = 1000;
			}if (menu.pressed() == 1 and isEditMenu) {
				switchToEditor();
			}MenuSelect.restart();
		}
		//cout << menu.pressed();
	}


	if (Keyboard::isKeyPressed(Keyboard::Escape) or Joystick::isButtonPressed(0, 7)) {
		if (isPlaying) {
			pagenum = 2000;
			doDrawGameWhilePause = true;

		}
		if (isControls or isSounds) {
			if (MenuSelect.getElapsedTime().asSeconds() > .300) {
				pagenum = 1;
				MenuSelect.restart();
			}
		}
		if (isEditMenu) {
			if (MenuSelect.getElapsedTime().asSeconds() > .300) {
				pagenum = 1000;
				menu.setSelected(1);
				menu.moveUp();

				MenuSelect.restart();
			}
		}
		if (isEditing) {
			if (MenuSelect.getElapsedTime().asSeconds() > .300) {
				pagenum = 13; isEditing = false;
				mapReference.setCurrentMap(0);
				mapReference.setLevels({ "Assets/Map/labMap/mapLabSpawn.txt", "Assets/Map/labMap/mapLabRoom1.txt", "Assets/Map/labMap/mapLabRoom2.txt", "Assets/Map/labMap/mapLabBossRoom.txt" },
									   { true, false, false, false });
				mapReference.loadLab(tileMap, *player, mapReference.getLevels()[0]);
				menu.setSelected(1);
				MenuSelect.restart();
			}
		}
		if (isOption and !isControls and !isSounds) {
			if (MenuSelect.getElapsedTime().asSeconds() > .300) {
				pagenum = 1000;
				if (menu.pressed() == 0) {
					menu.moveDown();
				}
				if (menu.pressed() == 2) {
					menu.moveUp();
				}
				MenuSelect.restart();
			}
		}
		if (isCredits) {
			if (MenuSelect.getElapsedTime().asSeconds() > .300) {
				pagenum = 1000;
				menu.setSelected(1);
				menu.moveUp();
				menu.moveUp();
				MenuSelect.restart();
			}
		}
		if (isControls or isSounds) {
			if (MenuSelect.getElapsedTime().asSeconds() > .300) {
				pagenum = 1;
				MenuSelect.restart();
			}
		}
		if (isStats) {
			if (MenuSelect.getElapsedTime().asSeconds() > .300) {
				pagenum = 2000;
				MenuSelect.restart();
			}
		}
	}

	if (isMenu or isOption or isPause or isEditMenu) {
		if (Keyboard::isKeyPressed(Keyboard::Up) or Joystick::getAxisPosition(0, Joystick::Y) < -50.f or Joystick::getAxisPosition(0, Joystick::PovY) < -50.f) {
			if (isMenu or isOption or isPause or isEditMenu and !isControls and !isSounds) {
				if (MenuSelect.getElapsedTime().asSeconds() > .300) {
					menu.moveUp();
					MenuSelect.restart();
					cout << isPause;
					cout << menu.pressed();
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) or Joystick::getAxisPosition(0, Joystick::Y) > 50.f or Joystick::getAxisPosition(0, Joystick::PovY) > 50.f) {
			if (isMenu or isOption or isPause or isEditMenu and !isControls and !isSounds) {
				if (MenuSelect.getElapsedTime().asSeconds() > .300) {
					menu.moveDown();
					MenuSelect.restart();
					cout << isPause;
					cout << menu.pressed();
				}
			}
		}
	}


	if (pagenum == -1) {
		window.close();
	}
	if (pagenum == 0) {
		if (isFirstStart) {
			PName(window, PlayerName);
			unscale();
		}

		else {
			isPlaying = true;
		}
	}
	if (pagenum == 13 and !isEditing) {
		isMenu = false;
		isPlaying = false;
		isEditMenu = true;
	}


	if (pagenum == 1) {
		isOption = true, isMenu = false, isPause = false, isSounds = false, isControls = false;
	}
	if (pagenum == 2) {
		isMenu = false;
		isCredits = true;
	}
	if (pagenum == 3) {
		isPause = false;
		isOption = false;
		isPlaying = true;
	}
	if (pagenum == 4) {
		//Sounds
		isSounds = true;
	}if (pagenum == 5) {
		//Controls
		isControls = true;
	}if (pagenum == 6) {
		//Stats
		isStats = true;
	}if (pagenum == 1000) {
		menu.rescale();
		isMenu = true;
		isOption = false;
		isEditMenu = false;
		isCredits = false;
	}if (pagenum == 2000) {
		isPlaying = false;
		isPause = true;
		isStats = false;
	}
}

void Game::gameLoop() {
	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			if (isEditing) {
				if (event.type == Event::MouseWheelScrolled) {
					Vector2f camSize = player->getCamera()->getSize();
					if (camSize.x <= 1920 * 1.5f)
					{
						if (event.mouseWheelScroll.delta < 0) {
							player->getCamera()->setSize(camSize * 1.1f);
						}
					}
					if (camSize.x >= 1920 / 5.f)
					{
						if (event.mouseWheelScroll.delta > 0) {
							player->getCamera()->setSize(camSize / 1.1f);
						}
					}
				}
				if (event.type == Event::MouseButtonPressed) {
					Vector2i mouseWorldPos = Vector2i(window.mapPixelToCoords(Mouse::getPosition(window)));
					if (Mouse::isButtonPressed(Mouse::Left)) {
						cout << mouseWorldPos.x / tileRes << " | " << mouseWorldPos.y / tileRes << endl;
						if (editTilesList.getGlobalBounds().contains(Vector2f(mouseWorldPos)))
						{
							for (int i = 0; i < editTilesVector.size(); i++) {
								vector<Sprite*> vect = editTilesVector[i];
								for (int k = 0; k < vect.size(); k++) {
									Sprite* tile = vect[k];
									if (tile->getGlobalBounds().contains(Vector2f(mouseWorldPos))) {
										tileSelected = editTileCharMap[tile];
									}
								}
							}
						}
						else
						{
							string currentMapPath = mapReference.getLevels()[mapReference.getCurrentMap()];
							fstream mapStream(currentMapPath);
							mapStream.seekp(mouseWorldPos.y / tileRes * (xSize + 2) + mouseWorldPos.x / tileRes);
							mapStream.write(&tileSelected, 1);
							mapStream.flush();
							mapReference.loadLab(tileMap, *player, currentMapPath);
						}
					}
					else if (Mouse::isButtonPressed(Mouse::Right)) {
						if (!editTilesList.getGlobalBounds().contains(Vector2f(mouseWorldPos))) {
							string currentMapPath = mapReference.getLevels()[mapReference.getCurrentMap()];
							fstream mapStream(currentMapPath);
							mapStream.seekp(mouseWorldPos.y / tileRes * (xSize + 2) + mouseWorldPos.x / tileRes);
							mapStream.write("-", 1);
							mapStream.flush();
							mapReference.loadLab(tileMap, *player, currentMapPath);
						}
					}
				}
			}
			if (isEditMenu and !isEditing) {
				if (event.type == Event::MouseButtonPressed) {
					Vector2i mouseWorldPos = Vector2i(window.mapPixelToCoords(Mouse::getPosition(window)));
					if (Mouse::isButtonPressed(Mouse::Left)) {
						for (int i = 0; i < mapFileSelectorBoxes.size(); i++) {
							FloatRect rect = mapFileSelectorBoxes[i];
							if (rect.contains(Vector2f(mouseWorldPos))) {
								isMenu = false;
								isEditMenu = false;
								isEditing = true;

								vector<string> levelsVector = {};
								vector<bool> levelsColorsVector = {};
								string firstMapPath;
								int fileCount = 0;
								for (const auto& entry : directory_iterator(mapFileSelectorPaths[i])) {
									fileCount++;
									if (fileCount == 1) {
										firstMapPath = entry.path().string();
									}
									levelsVector.push_back(entry.path().string());
									levelsColorsVector.push_back(false);
								}
								if (fileCount > 0) {
									mapReference.setLevels(levelsVector, levelsColorsVector);
									mapReference.setCurrentMap(0);
									mapReference.loadLab(tileMap, *player, firstMapPath);

									fstream map(firstMapPath);
									string line;
									xSize = 0;
									ySize = 0;
									while (true) {
										getline(map, line);
										if (line == ";") {
											break;
										}
										if (line.size() > 0) {
											if (line[0] == ';') {
												break;
											}
										}
										xSize = line.size();
										ySize++;
									}
									cout << endl << xSize << " | " << ySize << endl;
									editorGrid = EditorGrid(xSize, ySize);
									player->entitySprite.setPosition(xSize * tileRes / 2, ySize * tileRes / 2);
									player->getCamera()->setCenter(xSize * tileRes / 2, ySize * tileRes / 2);

									player->getCamera()->setSize(1920 / 1.7f, 1080 / 1.7f);
								}
								else {
									string newLevelPath = createLevelFile(mapFileSelectorPaths[i]);
									fstream mapStream(newLevelPath);
									char line[lineSize + 1];
									for (int i = 0; i < lineSize; i++) {
										line[i] = '-';
									}
									line[lineSize] = '\n';
									for (int i = 0; i < lineSize; i++) {
										mapStream.write(line, lineSize + 1);
									}
									mapStream.write(";", 1);
									mapStream.flush();

									mapReference.setLevels({ newLevelPath }, { false });
									mapReference.setCurrentMap(0);
									mapReference.loadLab(tileMap, *player, newLevelPath);

									editorGrid = EditorGrid(lineSize, lineSize);
									player->entitySprite.setPosition(lineSize * tileRes / 2, lineSize * tileRes / 2);
									player->getCamera()->setCenter(lineSize * tileRes / 2, lineSize * tileRes / 2);

									player->getCamera()->setSize(1920 / 1.7f, 1080 / 1.7f);

									for (const auto& entry : directory_iterator("Assets/Map/customMaps"))
									{
										cout << entry.path() << endl;
									}
								}
							}
						}
					}
				}
			}
		}

		update();
		display();

	}
	
	cout << "\nEnd of the game!" << endl;
	if (manager->getAllMedusas().size() == 0) {
		cout << "\nCongratulations " << PlayerName << " ! \n You have now restored the order of this world ! \n  We thank you very much <3";
	}
}

void Game::PName(RenderWindow& window, string& name) {
	font.loadFromFile("Assets/Font/pixel.ttf");
	if (!name.empty()) {
		name.clear();
	}
	Text t1, t2;
	t1.setFont(font);
	t2.setFont(font);
	t1.setString("Enter your name");
	t1.setPosition(Vector2f{ 10,300 });
	t2.setPosition(Vector2f{ 10,400 });
	t1.setFillColor(Color{ 255,204,0 });
	t2.setFillColor(Color{ 255,204,0 });

	Event event;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::TextEntered) {
				name += static_cast<char>(event.text.unicode);
			}
			if (Keyboard::isKeyPressed(Keyboard::Backspace) and name.size() > 0) {
				name.resize(name.size() - 1);
				if (Keyboard::isKeyPressed(Keyboard::LControl) or Keyboard::isKeyPressed(Keyboard::RControl)) {
					name.resize(0);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) and name.size() > 1) {
				pagenum = 0;
				isFirstStart = false;
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				pagenum = 1000;
				return;
			}
		}
		t2.setString(name);
		window.clear();
		window.draw(t1);
		window.draw(t2);
		window.display();
	}
}

void Game::unscale() {
	for (float i = 4.75; i > .5; i -= .1) {
		window.clear();
		menu.titlescreen.setScale(i, i * 2);
		for (shared_ptr<Tile> tile : tileMap) {
			if (tile) {
				//if (tile->getLayer() == 0) {
				window.draw(*tile->getSprite());
				//}
			}
		}
		window.draw(menu.titlescreen);
		window.display();
		isMenu = false;
	}
}
