#pragma once
#include "Entity.h"
#include "Outils.h"
#include "HUD.h"
#include "Animation.h"

class Player : public Entity
{
private :
	int money = 0;
	bool playerTookDamage = false;
	float speed;
	Clock damageClock;
	shared_ptr<View> camera = make_shared<View>();

public :
	Sprite playerJumpEffectSprite;
	Texture playerJumpEffectTexture;
	Sprite playerLandEffectSprite;
	Texture playerLandEffectTexture;

	bool isDashing = false;
	bool isCrouching = false;
	bool isJumping = false;
	bool isClimbing = false;
	bool isShooting = false;
	bool playerLastDirection = false;

	Player(Vector2f _pos, Texture& _textPlayer, Texture& _textPlayerJumpEffect, Texture& _textPlayerLandEffect, float _speed, int _hp);

	FloatRect getHitBox() override;
	void setMoney(int _money, HUD* hud);

	void takeDamage(int _damages,HUD* hud);
	int getMoney() const;
	float getSpeed();
	shared_ptr<View> getCamera() const;
	void setCamera();
	Vector2f getFeetPos();
};

