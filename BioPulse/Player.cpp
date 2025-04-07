#include "Player.h"

Player::Player(Vector2f _pos, Texture& _textPlayer, Texture& _textPlayerJumpEffect, Texture& _textPlayerLandEffect, float _speed, int _hp) : speed(_speed), playerJumpEffectTexture(_textPlayerJumpEffect), playerLandEffectTexture(_textPlayerLandEffect), Entity(_pos, _textPlayer, _hp)
{
	entitySprite.setOrigin(Vector2f(entityText.getSize().y / 2.f, entityText.getSize().y / 2.f));
	playerJumpEffectSprite.setTexture(playerJumpEffectTexture);
	playerLandEffectSprite.setTexture(playerLandEffectTexture);
	playerJumpEffectSprite.setOrigin(Vector2f(playerJumpEffectTexture.getSize().y / 2.f, playerJumpEffectTexture.getSize().y / 2.f));
	playerLandEffectSprite.setOrigin(Vector2f(playerLandEffectTexture.getSize().y / 2.f, playerLandEffectTexture.getSize().y / 2.f));
	playerJumpEffectSprite.setTextureRect(IntRect(0, 0, playerJumpEffectTexture.getSize().y, playerJumpEffectTexture.getSize().y));
	playerLandEffectSprite.setTextureRect(IntRect(0, 0, playerLandEffectTexture.getSize().y, playerLandEffectTexture.getSize().y));
	playerJumpEffectSprite.setColor(sf::Color::Transparent);
	playerLandEffectSprite.setColor(sf::Color::Transparent);
    camera->setSize(1920 / 2, 1080 / 2);
	entityType = "Player";
}

FloatRect Player::getHitBox()
{
	if (isCrouching)
	{
		Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
		Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
		return FloatRect(boundsPos.x + boundsSize.x / 4.f, boundsPos.y + boundsSize.y / 2.f, boundsSize.x / 2.f, boundsSize.y / 2.f);
	}
	else
	{
		Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
		Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
		return FloatRect(boundsPos.x + boundsSize.x / 4.f, boundsPos.y, boundsSize.x / 2.f, boundsSize.y);
	}
}

void Player::setMoney(int _money,HUD* hud) {
	money = _money;
	if (money == 10) {
		setMoney(0,hud);
		setHealth(health + 1);
		hud->addPlayerHP(1);
		isUpdateHP = true;
	}
}

void Player::takeDamage(int _damages,HUD* hud) {
	if (damageClock.getElapsedTime().asSeconds() >= playerDamageDetlaTime)
	{
		damageClock.restart();
		hud->isAnimDone = false;
		playerTookDamage = true;
		health -= _damages;
		if (health <= 0) //Tp le joueur au dernier cheackpoint
		{
			//entitySprite.setPosition(0, 0);
			health = 15;
		}
	}
}

int Player::getMoney() const { return money; }

float Player::getSpeed() { return speed; }
shared_ptr<View> Player::getCamera() const { return camera; }
void Player::setCamera() { camera->setCenter(entitySprite.getPosition() - Vector2f(0, tileRes*1.5f)); }

Vector2f Player::getFeetPos()
{
	return entitySprite.getPosition() + Vector2f(0, entityText.getSize().y / 2 - 1);
}
