#include "HUD.h"
HUD::HUD() {

	monnaie.setTexture(text.monnaieTexture);
	monnaie.setScale(.5, .5);

	monnaieCount0.setTexture(text.monnaieCount0Texture);
	monnaieCount0.setScale(.5, .5);
	monnaieCount1.setTexture(text.monnaieCount1Texture);
	monnaieCount1.setScale(.5, .5);

	monnaieCount2.setTexture(text.monnaieCount2Texture);
	monnaieCount2.setScale(.5, .5);

	monnaieCount3.setTexture(text.monnaieCount3Texture);
	monnaieCount3.setScale(.5, .5);

	monnaieCount4.setTexture(text.monnaieCount4Texture);
	monnaieCount4.setScale(.5, .5);

	monnaieCount5.setTexture(text.monnaieCount5Texture);
	monnaieCount5.setScale(.5, .5);

	monnaieCount6.setTexture(text.monnaieCount6Texture);
	monnaieCount6.setScale(.5, .5);

	monnaieCount7.setTexture(text.monnaieCount7Texture);
	monnaieCount7.setScale(.5, .5);

	monnaieCount8.setTexture(text.monnaieCount8Texture);
	monnaieCount8.setScale(.5, .5);

	monnaieCount9.setTexture(text.monnaieCount9Texture);
	monnaieCount9.setScale(.5, .5);

	playerIcon.setTexture(text.playerIconTexture);
	playerIcon.setScale(.4, .4);
	playerIcon.setTextureRect(IntRect(0, 0, text.playerIconTexture.getSize().y, text.playerIconTexture.getSize().y));

}


void HUD::createPlayerHP(int i){
	playerHP.clear();
	for (int j = 0; j < i; j++) {
		Sprite hp;
		hp.setTexture(text.playerDamagedTexture);
		hp.setScale(.5, .5);
		hp.setTextureRect(IntRect(0, 0, text.playerDamagedTexture.getSize().y, text.playerDamagedTexture.getSize().y));
		playerHP.push_back(hp);
	}
}

void HUD::addPlayerHP(int i) {
	for (int j = 0; j < i; j++) {
		Sprite hp;
		hp.setTexture(text.playerHealedTexture);
		hp.setScale(.5, .5);
		hp.setTextureRect(IntRect(0, 0, text.playerHealedTexture.getSize().y, text.playerHealedTexture.getSize().y));
		playerHP.insert(playerHP.begin(), hp);
	}
}

void HUD::addPlayerMoney(int i){
	monnaieCountTotal.clear();
	Sprite monnaieCount;
	switch (i) {
	case 0:
		monnaieCount.setTexture(text.monnaieCount0Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 1:
		monnaieCount.setTexture(text.monnaieCount1Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 2:
		monnaieCount.setTexture(text.monnaieCount2Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 3:
		monnaieCount.setTexture(text.monnaieCount3Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 4:
		monnaieCount.setTexture(text.monnaieCount4Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 5:
		monnaieCount.setTexture(text.monnaieCount5Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 6:
		monnaieCount.setTexture(text.monnaieCount6Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 7:
		monnaieCount.setTexture(text.monnaieCount7Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 8:
		monnaieCount.setTexture(text.monnaieCount8Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 9:
		monnaieCount.setTexture(text.monnaieCount9Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		break;
	case 10:
		Sprite monnaieCount1;
		monnaieCount.setTexture(text.monnaieCount1Texture);
		monnaieCount1.setTexture(text.monnaieCount0Texture);
		monnaieCount.setScale(.5, .5);
		monnaieCount1.setScale(.5, .5);
		monnaieCountTotal.push_back(monnaieCount);
		monnaieCountTotal.push_back(monnaieCount1);
		break;
	}
	
}
void HUD::updateMoney(int i){

}

void HUD::drawHUD(RenderWindow& window, Vector2f pos) {
	drawPlayerHP(window,pos);
	drawIcon(window,pos);
	drawMoney(window,pos);
}

void HUD::drawIcon(RenderWindow& window, Vector2f pos){
	playerIcon.setPosition(Vector2f(pos.x-230, pos.y+40));
	window.draw(playerIcon);
}

void HUD::drawPlayerHP(RenderWindow& window, Vector2f pos){
	for (int i = 0; i < playerHP.size(); i++) {
		playerHP[i].setPosition(Vector2f(pos.x - 60 - (i+ abs((int)playerHP.size()-15)) * 10, pos.y + 45));
		window.draw(playerHP[i]);
	}
}

void HUD::drawMoney(RenderWindow& window, Vector2f pos){
	monnaie.setPosition(Vector2f(pos.x - 190, pos.y + 62));
	window.draw(monnaie);
	for (int i = 0; i < monnaieCountTotal.size(); i++) {
		monnaieCountTotal[i].setPosition(Vector2f(pos.x-150 +i*10, pos.y + 65));
		window.draw(monnaieCountTotal[i]);
	}
}

vector<Sprite> HUD::getPlayerHP() const {
	return playerHP;
}