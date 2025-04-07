#pragma once
#include "Entity.h"
#include "Outils.h"

class Pet : public Entity
{
private:
	float posYforidle;
	bool gotoplayer;
	bool goupidle;
	bool platformside;
	Vector2f playerposplatforme;
	Clock updateClock;
	Time updateTime;
	Clock platformClock;
	Time platformTime;
	
public:

	bool petisaplatform;
	bool newplatform;

	Text petDialogue;
	Font petFont;
	Clock dialogueClock;
	bool showDialogue;

	Sprite dialogueBoxSprite; 
	Texture dialogueBoxTexture; 

	bool petIsGoingToPlatform;
	bool petTransitionToPlatform;
	Pet(Vector2f _pos, Texture& _text);

	~Pet();

	void update(Vector2f playerPos);

	void becomeplatforme(Sprite& player, bool& playerdirection);

	FloatRect getHitBox() override;

};