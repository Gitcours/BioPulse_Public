#pragma once
#include "TextureManager.h"
#include "EntityManager.h"
#include "Animation.h"
#include "Projectiles.h"
#include "Outils.h"
#include "HUD.h"

extern Animation anim;
class InGameManagement
{
private :
	Clock waitClock;
	bool isJumping = false;
	bool isAttacking = false;
	bool playPlayerShootingAnim = false;
	bool playPlayerJumpEffectAnim = false;
	bool playPlayerLandEffectAnim = false;
	bool playerWasInTheAir = false;
	Clock playerEffectClock;
	int hpToRemove = 0;
public :

#include "HUD.h"
	void igManagement(EntityManager* manager,TextureManager& text,shared_ptr<Player> player, HUD *hud);
	void hudAnim(HUD* hud,int i);
	void healAnim(HUD* hud);
};

