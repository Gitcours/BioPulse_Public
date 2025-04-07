#include "Pet.h"

Pet::Pet(Vector2f _pos, Texture& _text) : Entity(_pos, _text, 0), updateTime(sf::milliseconds(1)), platformTime(sf::milliseconds(1)), posYforidle(entitySprite.getPosition().y), petisaplatform(false), gotoplayer(false), newplatform(true), petIsGoingToPlatform(false), petTransitionToPlatform(false) {
	entitySprite.setOrigin(Vector2f(entityText.getSize().y / 2.f, entityText.getSize().y / 2.f));
	entityType = "Pet";


	petFont.loadFromFile("Assets/Compagnon/SuperPlumberBrothers-y00V.ttf");
	if (!dialogueBoxTexture.loadFromFile("Assets/Compagnon/textFox.png")) {
		std::cerr << "Erreur de chargement de la texture de la boîte de dialogue !" << std::endl;
	}
	dialogueBoxSprite.setTexture(dialogueBoxTexture);
	dialogueBoxSprite.setScale(0.3f, 0.3f); 
	dialogueBoxSprite.setPosition(_pos.x, _pos.y - 70);
	petDialogue.setFont(petFont);
	petDialogue.setCharacterSize(10);
	petDialogue.setFillColor(Color::White);
	petDialogue.setString("Hello ! I'm here as your pet ! !");
	petDialogue.setPosition(_pos.x, _pos.y - 45); 
	showDialogue = true; 
}

Pet::~Pet() {
}

void Pet::update(Vector2f playerPos) {
	if (!petisaplatform && updateClock.getElapsedTime() >= updateTime) {
		updateClock.restart();
		float distance = std::sqrt(std::pow(playerPos.x - entitySprite.getPosition().x, 2) + std::pow(playerPos.y - entitySprite.getPosition().y, 2));
		if (distance > petdistancetofollowplayer)
		{
			gotoplayer = true;
		}

		if (gotoplayer) {
			Vector2f directionpet = Vector2f(playerPos.x, playerPos.y - 20) - entitySprite.getPosition();
			float length = std::sqrt(directionpet.x * directionpet.x + directionpet.y * directionpet.y);
			directionpet /= length;

			if (directionpet.x < 0)
			{
				entitySprite.setScale(-1.f, 1.f);
			}
			else
			{
				entitySprite.setScale(1.f, 1.f);
			}

			entitySprite.move(directionpet * petspeed);

			if (distance < petdistancetofollowplayer / 4)
			{
				gotoplayer = false;
				posYforidle = entitySprite.getPosition().y;
			}
		}

		if (!gotoplayer)
		{
			if (entitySprite.getPosition().y - posYforidle < -petidleoffset)
			{
				goupidle = true;
			}
			else if (entitySprite.getPosition().y - posYforidle > petidleoffset)
			{
				goupidle = false;
			}

			if (goupidle)
			{
				entitySprite.move(0, petidlespeed);
			}
			else
			{
				entitySprite.move(0, -petidlespeed);
			}
		}
		if (showDialogue) {
			dialogueBoxSprite.setPosition(entitySprite.getPosition().x - 20, entitySprite.getPosition().y - 70);
			petDialogue.setPosition(dialogueBoxSprite.getPosition().x + 30, dialogueBoxSprite.getPosition().y + dialogueBoxSprite.getGlobalBounds().height / 2 - petDialogue.getGlobalBounds().height / 2);

			if (dialogueClock.getElapsedTime().asSeconds() > 5) {
				showDialogue = false;
			}
		}
	}
}


void Pet::becomeplatforme(Sprite& player, bool& playerdirection)
{
	if (platformClock.getElapsedTime() >= platformTime)
	{
		platformClock.restart();
		Vector2f directionpet;

		if (newplatform)
		{
			newplatform = false;
			petTransitionToPlatform = true;
			playerposplatforme = player.getPosition();
			if (!playerdirection) {
				platformside = true;
			}
			else {
				platformside = false;
			}
		}

		if (platformside)
		{
			directionpet = Vector2f(playerposplatforme.x - petplatformdistancetoplayer, playerposplatforme.y) - entitySprite.getPosition();
		}
		else
		{
			directionpet = Vector2f(playerposplatforme.x + petplatformdistancetoplayer, playerposplatforme.y) - entitySprite.getPosition();
		}

		float length = std::sqrt(directionpet.x * directionpet.x + 1 + directionpet.y * directionpet.y);
		directionpet /= length;

		if (directionpet.x < 0)
		{
			entitySprite.setScale(-1.f, 1.f);
		}
		else
		{
			entitySprite.setScale(1.f, 1.f);
		}

		if (std::abs(entitySprite.getPosition().x - playerposplatforme.x) >= 59 && std::abs(entitySprite.getPosition().x - playerposplatforme.x) <= 61) 
		{
			petIsGoingToPlatform = false;
		}
		else
		{
			petIsGoingToPlatform = true;
		}
		entitySprite.move(directionpet * petspeed);
		if (showDialogue) {
			dialogueBoxSprite.setPosition(entitySprite.getPosition().x - 20, entitySprite.getPosition().y - 70);
			petDialogue.setPosition(dialogueBoxSprite.getPosition().x + 30, dialogueBoxSprite.getPosition().y + dialogueBoxSprite.getGlobalBounds().height / 2 - petDialogue.getGlobalBounds().height / 2);

			if (dialogueClock.getElapsedTime().asSeconds() > 20) {
				showDialogue = false;
			}
		}
	}
}

FloatRect Pet::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x + boundsSize.x / 5000.f, boundsPos.y + boundsSize.y / 2.3f, boundsSize.x / 1.f, boundsSize.y / 6.f);
}