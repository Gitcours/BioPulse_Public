#include "TextureManager.h"

void TextureManager::loadTexture()
{
	if (!idlePlayerRightText.loadFromFile("Assets/Player/playerIdleRight.png")) {};
	if (!idlePlayerLeftText.loadFromFile("Assets/Player/playerIdleLeft.png")) {};
	if (!runningPlayerLeftText.loadFromFile("Assets/Player/playerRunLeft.png")) {};
	if (!runningPlayerRightText.loadFromFile("Assets/Player/playerRunRight.png")) {};
	if (!jumpingPlayerLeftText.loadFromFile("Assets/Player/left_jump.png")) {};
	if (!jumpingPlayerRightText.loadFromFile("Assets/Player/right_jump.png")) {};
	if (!fallingPlayerRightText.loadFromFile("Assets/Player/right_fall.png")) {};
	if (!fallingPlayerLeftText.loadFromFile("Assets/Player/left_fall.png")) {};
	if (!crouchingPlayerLeftText.loadFromFile("Assets/Player/left_crouchWalk.png")) {};
	if (!crouchingPlayerRightText.loadFromFile("Assets/Player/right_crouchWalk.png")) {};
	if (!crouchingPlayerIdleText.loadFromFile("Assets/Player/crouch.png")) {};
	if (!dashPlayerLeftText.loadFromFile("Assets/Player/left_dash.png")) {};
	if (!dashPlayerRightText.loadFromFile("Assets/Player/right_dash.png")) {};
	if (!attackPlayerLeftText.loadFromFile("Assets/Player/left_shoot.png")) {};
	if (!attackPlayerRightText.loadFromFile("Assets/Player/right_shoot.png")) {};
	if (!hangingPlayerTextL.loadFromFile("Assets/Player/left_wallClimb.png")) {};
	if (!hangingPlayerTextR.loadFromFile("Assets/Player/right_wallClimb.png")) {};
	//if (!climbingPlayerText.loadFromFile("Assets/Player/playerClimbRight.png")) {};

	if (!jumpEffectPlayerText.loadFromFile("Assets/Player/jump_effect.png")) {};
	if (!landEffectPlayerText.loadFromFile("Assets/Player/land_effect.png")) {};

	if (!titelscreenTexture.loadFromFile("Assets/Menu/titlescreen.png"));
	if (!optionscreenTexture.loadFromFile("Assets/Menu/optionscreen.png"));
	if (!editormenuscreenTexture.loadFromFile("Assets/Menu/editormenuscreen.png"));
	if (!editTilesListTexture.loadFromFile("Assets/edit_tiles_list.png"));

	if (!pausebgl0Texture.loadFromFile("Assets/Menu/pausebgl0.png"));
	if (!pausebgl1Texture.loadFromFile("Assets/Menu/pausebgl1.png"));
	if (!pausebgl2Texture.loadFromFile("Assets/Menu/pausebgl2.png"));
	if (!silhouette_1Texture.loadFromFile("Assets/Menu/silhouette_1.png"));
	if (!silhouette_2Texture.loadFromFile("Assets/Menu/silhouette_2.png"));

	if (!monnaieTexture.loadFromFile("Assets/HUD/clam.png"));

	if (!monnaieCount0Texture.loadFromFile("Assets/HUD/numbers/0.png"));
	if (!monnaieCount1Texture.loadFromFile("Assets/HUD/numbers/1.png"));
	if (!monnaieCount2Texture.loadFromFile("Assets/HUD/numbers/2.png"));
	if (!monnaieCount3Texture.loadFromFile("Assets/HUD/numbers/3.png"));
	if (!monnaieCount4Texture.loadFromFile("Assets/HUD/numbers/4.png"));
	if (!monnaieCount5Texture.loadFromFile("Assets/HUD/numbers/5.png"));
	if (!monnaieCount6Texture.loadFromFile("Assets/HUD/numbers/6.png"));
	if (!monnaieCount7Texture.loadFromFile("Assets/HUD/numbers/7.png"));
	if (!monnaieCount8Texture.loadFromFile("Assets/HUD/numbers/8.png"));
	if (!monnaieCount9Texture.loadFromFile("Assets/HUD/numbers/9.png"));

	if (!playerDamagedTexture.loadFromFile("Assets/HUD/HP/damage_sheet.png"));
	if (!playerHealedTexture.loadFromFile("Assets/HUD/HP/heal_sheet.png"));

	if (!playerIconTexture.loadFromFile("Assets/HUD/player_icon_sheet.png"));
	Texture playerDamagedTexture, playerIconTexture;

	//TILESET
	if (!floorTileTexture.loadFromFile("Assets/Map/TileSet/Platforms-Walls/Hovering Platform/hovering_platform_simple.png"));
	if (!floorMiddleTileTexture.loadFromFile("Assets/Map/TileSet/Platforms-Walls/Hovering Platform/hovering_platform_middle.png"));
	if (!floorEndTileTexture.loadFromFile("Assets/Map/TileSet/Platforms-Walls/Hovering Platform/hovering_platform_left.png"));

	if (!wallTileTexture.loadFromFile("Assets/Map/TileSet/wall_side_tech.png"));
	if (!wallCornerInsideTileTexture.loadFromFile("Assets/Map/TileSet/wall_corner_inside_tech.png"));
	if (!wallCornerTileTexture.loadFromFile("Assets/Map/TileSet/wall_corner_tech.png"));
	if (!wallFloorTileTexture.loadFromFile("Assets/Map/TileSet/floor_1_tech.png"));
	if (!wallCeilingTexture.loadFromFile("Assets/Map/TileSet/ceiling_tech.png"));
	if (!wallPlainTileTexture.loadFromFile("Assets/Map/TileSet/wall_plain_tech.png"));

	if (!wallStickyTileTexture.loadFromFile("Assets/Map/TileSet/Platforms-Walls/Sticky Wall/sticky_wall_top.png"));
	if (!wallStickyBottomTileTexture.loadFromFile("Assets/Map/TileSet/Platforms-Walls/Sticky Wall/sticky_wall_bottom.png"));

	if (!doorTexture.loadFromFile("Assets/Map/TileSet/placeholderTuiles/door.png"));
	if (!climbTileTexture.loadFromFile("Assets/Map/TileSet/placeholderTuiles/Ladder.png"));

	if (!crabeText.loadFromFile("Assets/Ennemies/crab_walk.png"));
	if (!poissonGlobeIdleText.loadFromFile("Assets/Ennemies/fugu_idle.png"));
	if (!poissonGlobeGrownText.loadFromFile("Assets/Ennemies/fugu_charge.png"));
	if (!hippocampesText.loadFromFile("Assets/Ennemies/seahorse_idle.png"));
	if (!hippocampesShootText.loadFromFile("Assets/Ennemies/seahorse_shoot.png"));
	if (!bulletTexture.loadFromFile("Assets/Ennemies/seahorse_bullet.png"));
	
	if (medusaPhase1Text.loadFromFile("Assets/Ennemies/Medusa/Phase1.png"));
	if (medusaPhase2Text.loadFromFile("Assets/Ennemies/Medusa/Phase2.png"));
	if (medusaPhase3Text.loadFromFile("Assets/Ennemies/Medusa/Phase3.png"));

	if (!miniMText.loadFromFile("Assets/Ennemies/Medusa/miniM.png")) {};

	if (!tentacleAttackRiseText.loadFromFile("Assets/Ennemies/Medusa/AttackRise.png")) {};
	if (!tentacleAttackUnRiseText.loadFromFile("Assets/Ennemies/Medusa/AttackUnRise.png")) {};
	if (!tentacleAttackIdleRiseText.loadFromFile("Assets/Ennemies/Medusa/AttackRisedIdle.png")) {};
	if (!tentacleAttackText.loadFromFile("Assets/Ennemies/Medusa/AttackTent.png")) {};

	if (!tentacleJFGSummonText.loadFromFile("Assets/Ennemies/Medusa/summon.png")) {};
	if (!tentacleJFGSpawnText.loadFromFile("Assets/Ennemies/Medusa/summonSpawn.png")) {};

	if (!tentacleLaserSpawnText.loadFromFile("Assets/Ennemies/Medusa/wLaserSpawn.png")) {};
	if (!tentacleLaserUnSpawnText.loadFromFile("Assets/Ennemies/Medusa/wLaserUnSpawn.png")) {};
	if (!tentacleLaserBefoShootText.loadFromFile("Assets/Ennemies/Medusa/wLaserPreShoot.png")) {};

	if (!tentacleJellyFishGenIdleText.loadFromFile("Assets/Ennemies/Medusa/TentIdle1.png")) {};
	if (!tentacleAttackIdleText.loadFromFile("Assets/Ennemies/Medusa/TentIdle2.png")) {};
	if (!tentacleLaserIdleText.loadFromFile("Assets/Ennemies/Medusa/TentIdle3.png")) {};
	if (!projectileText.loadFromFile("Assets/Player/bullet.png"));

	if (!petIdleText.loadFromFile("Assets/Compagnon/Idle.png"));
	if (!petTransitionText.loadFromFile("Assets/Compagnon/transition.png"));
	if (!petPlatformText.loadFromFile("Assets/Compagnon/platform.png"));
	
	if (!laserText.loadFromFile("Assets/Ennemies/Medusa/laser.png")) {};

	if (!background_boss_room_1Texture.loadFromFile("Assets/BG/background_boss_room_1.png"));
	if (!background_room_1Texture.loadFromFile("Assets/BG/background_room_1.png"));
	if (!background_room_2Texture.loadFromFile("Assets/BG/background_room_2.png"));
	if (!background_room_3Texture.loadFromFile("Assets/BG/background_room_3.png"));
	if (!background_room_4Texture.loadFromFile("Assets/BG/background_room_4.png"));
	if(!creditsTexture.loadFromFile("Assets/BG/credits.png"));
	if (!icon.loadFromFile("Assets/Logo/game_icon.png"));
	if (!iconTexture.loadFromFile("Assets/Logo/logoToClean.png"));
}
TextureManager text;
