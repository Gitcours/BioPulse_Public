#pragma once
#include "Outils.h"

class TextureManager
{
public :
	Texture idlePlayerRightText;
	Texture idlePlayerLeftText;
	Texture runningPlayerRightText;
	Texture runningPlayerLeftText;
	Texture jumpingPlayerLeftText;
	Texture jumpingPlayerRightText;
	Texture fallingPlayerRightText;
	Texture fallingPlayerLeftText;
	Texture crouchingPlayerLeftText;
	Texture crouchingPlayerRightText;
	Texture crouchingPlayerIdleText;
	Texture dashPlayerLeftText;
	Texture dashPlayerRightText;
	Texture attackPlayerLeftText;
	Texture attackPlayerRightText;
	Texture hangingPlayerTextL;
	Texture hangingPlayerTextR;
	Texture climbingPlayerText;

	Texture jumpEffectPlayerText;
	Texture landEffectPlayerText;

	Texture projectileText;

	Texture petIdleText;
	Texture petTransitionText;
	Texture petPlatformText;

	Texture floorTileTexture;
	Texture floorMiddleTileTexture;
	Texture floorEndTileTexture;

	Texture wallTileTexture;
	Texture wallFloorTileTexture;
	Texture wallCornerTileTexture;
	Texture wallCornerInsideTileTexture;
	Texture wallCeilingTexture;
	Texture wallPlainTileTexture;

	Texture wallStickyTileTexture;
	Texture wallStickyBottomTileTexture;

	Texture doorTexture;
	Texture climbTileTexture;

	Texture laserText;
	Texture medusaPhase1Text;
	Texture medusaPhase2Text;
	Texture medusaPhase3Text;
	Texture miniMText;
	Texture tentacleAttackRiseText;
	Texture tentacleAttackUnRiseText;
	Texture tentacleAttackIdleRiseText;
	Texture tentacleAttackText;

	Texture tentacleJFGSummonText;
	Texture tentacleJFGSpawnText;

	Texture tentacleLaserSpawnText;
	Texture tentacleLaserUnSpawnText;
	Texture tentacleLaserBefoShootText;

	Texture tentacleLaserIdleText;
	Texture tentacleAttackIdleText;
	Texture tentacleJellyFishGenIdleText;

	Texture monnaieTexture,monnaieCount0Texture, monnaieCount1Texture,monnaieCount2Texture, monnaieCount3Texture, monnaieCount4Texture, monnaieCount5Texture, monnaieCount6Texture, monnaieCount7Texture, monnaieCount8Texture, monnaieCount9Texture;

	Texture playerHealedTexture,playerDamagedTexture, playerIconTexture;
	Texture titelscreenTexture, optionscreenTexture, editormenuscreenTexture;
	Texture editTilesListTexture;

	Texture pausebgl0Texture, pausebgl1Texture,pausebgl2Texture, silhouette_1Texture, silhouette_2Texture;

	Texture bulletTexture;
	Texture crabeText;
	Texture poissonGlobeIdleText;
	Texture poissonGlobeGrownText;
	Texture hippocampesText;
	Texture hippocampesShootText;
	Texture creditsTexture;
	Texture background_boss_room_1Texture, background_room_1Texture, background_room_2Texture, background_room_3Texture, background_room_4Texture;

	Image icon;
	Texture iconTexture;

	void loadTexture();
};

extern TextureManager text;

