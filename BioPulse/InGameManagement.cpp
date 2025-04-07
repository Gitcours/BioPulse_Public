#include "InGameManagement.h"
Animation anim;
void InGameManagement::igManagement(EntityManager* manager, TextureManager& text, shared_ptr<Player> player, HUD* hud)
{
	shared_ptr<Entity> ePet = manager->getAllPets()[0];
	shared_ptr<Pet> pet = dynamic_pointer_cast<Pet>(ePet);
	Clock deltaTime2;

	while (isGameRunning)
	{
		while (isPause or isMenu or isEditMenu or isEditing or isOption) { timePassed = deltaTime2.restart().asSeconds(); }
		timePassed = deltaTime2.restart().asSeconds();
		std::cout << player->getHealth() << std::endl;
		if (!isEditing) {
			player->setCamera();
		}

		if (player->isShooting && !playPlayerShootingAnim) {
			playPlayerShootingAnim = true;
		}

		if (player->animClock.getElapsedTime().asSeconds() >= playerFrame)
		{
			player->animClock.restart();
			if (anim.continueAnimation(player->entitySprite) == 1 && (player->entitySprite.getTexture() == &text.attackPlayerLeftText || player->entitySprite.getTexture() == &text.attackPlayerRightText))
			{
				playPlayerShootingAnim = false;
			}
		}

		if (playerEffectClock.getElapsedTime().asSeconds() >= playerEffectFrame)
		{
			playerEffectClock.restart();
			if (playPlayerJumpEffectAnim)
			{
				if (anim.continueAnimation(player->playerJumpEffectSprite) == 1)
				{
					playPlayerJumpEffectAnim = false;
				}
			}
			if (playPlayerLandEffectAnim)
			{
				if (anim.continueAnimation(player->playerLandEffectSprite) == 1)
				{
					playPlayerLandEffectAnim = false;
				}
			}
		}
		if (!playPlayerJumpEffectAnim)
		{
			player->playerJumpEffectSprite.setColor(Color::Transparent);
		}
		if (!playPlayerLandEffectAnim)
		{
			player->playerLandEffectSprite.setColor(Color::Transparent);
		}

		pet->update(player->entitySprite.getPosition());

		if (pet->animClock.getElapsedTime().asSeconds() >= petFrame)
		{
			pet->animClock.restart();
			if (anim.continueAnimation(pet->entitySprite) == 1 && pet->entitySprite.getTexture() == &text.petTransitionText) {
				pet->petTransitionToPlatform = false;
			}
		}
		if (pet->petisaplatform)
		{
			if (pet->petTransitionToPlatform && manager->getAllPets()[0]->entitySprite.getTexture() != &text.petTransitionText)
			{
				pet->entitySprite.setTexture(text.petTransitionText);
				pet->entitySprite.setTextureRect(IntRect(0, 0, pet->entitySprite.getTextureRect().height, pet->entitySprite.getTextureRect().height));
				petFrame = 0.1f;
			}
			else if (!pet->petTransitionToPlatform && manager->getAllPets()[0]->entitySprite.getTexture() != &text.petPlatformText)
			{
				pet->entitySprite.setTexture(text.petPlatformText);
				pet->entitySprite.setTextureRect(IntRect(0, 0, pet->entitySprite.getTextureRect().height, pet->entitySprite.getTextureRect().height));
				petFrame = 0.1f;
			}
		}
		else if (pet->entitySprite.getTexture() != &text.petIdleText)
		{
			pet->entitySprite.setTexture(text.petIdleText);
			pet->entitySprite.setTextureRect(IntRect(0, 0, pet->entitySprite.getTextureRect().height, pet->entitySprite.getTextureRect().height));
			petFrame = 0.1f;
		}

		if (player->entitySprite.getTexture() != &text.hangingPlayerTextL and player->entitySprite.getTexture() != &text.hangingPlayerTextR) {
			player->entitySprite.setScale(1, 1);
			if (!isGrounded)
			{
				if (player->isDashing) {
					if (!player->playerLastDirection && player->entitySprite.getTexture() != &text.dashPlayerLeftText)
					{
						player->playerLastDirection = false;
						player->entitySprite.setTexture(text.dashPlayerLeftText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					else if (player->playerLastDirection && player->entitySprite.getTexture() != &text.dashPlayerRightText)
					{
						player->playerLastDirection = true;
						player->entitySprite.setTexture(text.dashPlayerRightText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					playerFrame = 0.f;
				}
				else if (direction.y > 0) {
					if (!player->playerLastDirection && player->entitySprite.getTexture() != &text.fallingPlayerLeftText)
					{
						player->entitySprite.setTexture(text.fallingPlayerLeftText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					else if (player->playerLastDirection && player->entitySprite.getTexture() != &text.fallingPlayerRightText)
					{
						player->entitySprite.setTexture(text.fallingPlayerRightText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
				}
				else
				{
					if (!player->playerLastDirection && player->entitySprite.getTexture() != &text.jumpingPlayerLeftText)
					{
						player->playerLastDirection = false;
						player->entitySprite.setTexture(text.jumpingPlayerLeftText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					else if (player->playerLastDirection && player->entitySprite.getTexture() != &text.jumpingPlayerRightText)
					{
						player->playerLastDirection = true;
						player->entitySprite.setTexture(text.jumpingPlayerRightText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
				}

				playerFrame = 0.5f;

				if (player->isJumping && !playPlayerJumpEffectAnim)
				{
					//std::cout << "Jump effect" << std::endl;
					playPlayerJumpEffectAnim = true;
					player->playerJumpEffectSprite.setColor(Color::White);
					player->playerJumpEffectSprite.setTextureRect(IntRect(0, 0, player->playerJumpEffectTexture.getSize().y, player->playerJumpEffectTexture.getSize().y));
					player->playerJumpEffectSprite.setTextureRect(IntRect(0, 0, player->playerJumpEffectTexture.getSize().y, player->playerJumpEffectTexture.getSize().y));
				}
				playPlayerLandEffectAnim = false;
				playerWasInTheAir = true;
			}

			else if (player->isDashing) {
				if (!player->playerLastDirection && player->entitySprite.getTexture() != &text.dashPlayerLeftText)
				{
					player->playerLastDirection = false;
					player->entitySprite.setTexture(text.dashPlayerLeftText);
					player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
				}
				else if (player->playerLastDirection && player->entitySprite.getTexture() != &text.dashPlayerRightText)
				{
					player->playerLastDirection = true;
					player->entitySprite.setTexture(text.dashPlayerRightText);
					player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
				}
				playerFrame = 0.f;
			}

			else if ((Keyboard::isKeyPressed(Keyboard::Scancode::A) || Keyboard::isKeyPressed(Keyboard::Scancode::D) || Joystick::getAxisPosition(0, Joystick::X) < -50.f || Joystick::getAxisPosition(0, Joystick::X) > 50.f) and !isStill)
			{
				if (playerWasInTheAir)
				{
					if (playPlayerJumpEffectAnim)
					{
						playPlayerJumpEffectAnim = false;
					}
					if (!playPlayerLandEffectAnim)
					{
						playPlayerLandEffectAnim = true;
						player->playerLandEffectSprite.setColor(Color::White);
						player->playerLandEffectSprite.setTextureRect(IntRect(0, 0, player->playerLandEffectTexture.getSize().y, player->playerLandEffectTexture.getSize().y));
						player->playerLandEffectSprite.setPosition(player->entitySprite.getPosition().x, player->entitySprite.getPosition().y);
					}
					playerWasInTheAir = false;
				}
				player->playerJumpEffectSprite.setPosition(player->entitySprite.getPosition().x, player->entitySprite.getPosition().y);
				playPlayerShootingAnim = false;
				if (player->isCrouching)
				{
					if (!player->playerLastDirection && player->entitySprite.getTexture() != &text.crouchingPlayerLeftText)
					{
						player->entitySprite.setTexture(text.crouchingPlayerLeftText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					else if (player->playerLastDirection && player->entitySprite.getTexture() != &text.crouchingPlayerRightText)
					{
						player->entitySprite.setTexture(text.crouchingPlayerRightText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					playerFrame = 0.2f;
				}
				else
					if (!player->playerLastDirection && player->entitySprite.getTexture() != &text.runningPlayerLeftText)
					{
						player->entitySprite.setTexture(text.runningPlayerLeftText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					else if (player->playerLastDirection > 0.f && player->entitySprite.getTexture() != &text.runningPlayerRightText)
					{
						player->entitySprite.setTexture(text.runningPlayerRightText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
				playerFrame = 0.1f;
			}

			else if ((Mouse::isButtonPressed(Mouse::Left) || Joystick::getAxisPosition(0, Joystick::Z) < -0.5f) && playPlayerShootingAnim)
			{
				if (!player->playerLastDirection && player->entitySprite.getTexture() != &text.attackPlayerLeftText) {
					player->entitySprite.setTexture(text.attackPlayerLeftText);
					player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
				}
				else if (player->playerLastDirection && player->entitySprite.getTexture() != &text.attackPlayerRightText) {
					player->entitySprite.setTexture(text.attackPlayerRightText);
					player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
				}
				playerFrame = bulletdeltaTime / 5.f;
			}

			else
			{
				if (playerWasInTheAir)
				{
					if (playPlayerJumpEffectAnim)
					{
						playPlayerJumpEffectAnim = false;
					}
					if (!playPlayerLandEffectAnim)
					{
						playPlayerLandEffectAnim = true;
						player->playerLandEffectSprite.setColor(Color::White);
						player->playerLandEffectSprite.setTextureRect(IntRect(0, 0, player->playerLandEffectTexture.getSize().y, player->playerLandEffectTexture.getSize().y));
						player->playerLandEffectSprite.setPosition(player->entitySprite.getPosition().x, player->entitySprite.getPosition().y);
					}
					playerWasInTheAir = false;
				}
				player->playerJumpEffectSprite.setPosition(player->entitySprite.getPosition().x, player->entitySprite.getPosition().y);
				playPlayerShootingAnim = false;
				if (player->isCrouching) {
					if (player->entitySprite.getTexture() != &text.crouchingPlayerIdleText)
					{
						player->entitySprite.setTexture(text.crouchingPlayerIdleText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					playerFrame = 0.3f;
				}
				else
				{
					if (!player->playerLastDirection && player->entitySprite.getTexture() != &text.idlePlayerLeftText)
					{
						player->entitySprite.setTexture(text.idlePlayerLeftText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					else if (player->playerLastDirection && player->entitySprite.getTexture() != &text.idlePlayerRightText)
					{
						player->entitySprite.setTexture(text.idlePlayerRightText);
						player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
					}
					playerFrame = 0.3f;
				}
			}
		}

		managerMutex.lock();
		//wdwdwdwdwdwdwdwd
		hudAnim(hud, hpToRemove);
		healAnim(hud);

		//if (hud->animClock.getElapsedTime().asSeconds() >= 0.1) {
		//	hud->animClock.restart();
		//	if (!hud->isAnimDone) {

		//		if (anim.continueAnimation(hud->playerHP.front()) == 1)
		//		{
		//			hud->isAnimDone = true;
		//			hud->playerHP.erase(hud->playerHP.begin());
		//		}
		//	}
		//}
		for (int i = 0; i < manager->getAllEntities().size(); i++)
		{
			shared_ptr<Entity> entity = manager->getAllEntities()[i];

			if (entity->entityType == "Projectiles")
			{
				shared_ptr<Projectiles> projectile = dynamic_pointer_cast<Projectiles>(entity);
				projectile->update();

				for (auto j = 0; j < manager->getAllEnnemies().size(); j++)
				{
					if (projectile->getHitBox().intersects(manager->getAllEnnemies()[j]->getHitBox()))
					{
						manager->deleteEntity(entity);
						manager->getAllEnnemies()[j]->setHealth(manager->getAllEnnemies()[j]->getHealth() - playerBulletDamage);
						if (manager->getAllEnnemies()[j]->getHealth() <= 0)
						{
							manager->deleteEntity(manager->getAllEnnemies()[j]);
						}
						break;
					}
				}

				if (player->getCamera()->getCenter().x - bulletdistancetocentercameratodie > projectile->entitySprite.getPosition().x || player->getCamera()->getCenter().x + bulletdistancetocentercameratodie < projectile->entitySprite.getPosition().x) {
					manager->deleteEntity(entity);
				}

				else if (projectile->animClock.getElapsedTime().asSeconds() >= playerbulletFrame) {
					projectile->animClock.restart();
					anim.continueAnimation(projectile->entitySprite);
				}
			}

			else if (entity->entityType == "Crabe")
			{
				shared_ptr<Crabe> crabe = dynamic_pointer_cast<Crabe>(entity);

				if (crabe->getHitBox().intersects(player->getHitBox())) {
					if (crabe->getHitBox().top + 2 >= player->getHitBox().top + player->getHitBox().height)
					{
						manager->deleteEntity(entity);
					}
					else
					{
						player->takeDamage(1, hud);
						hpToRemove = 1;
					}
				}

				else if (crabe->animClock.getElapsedTime().asSeconds() >= crabeFrame)
				{
					crabe->animClock.restart();
					anim.continueAnimation(crabe->entitySprite);
				}
			}

			else if (entity->entityType == "Hippocampe")
			{
				shared_ptr<Hippocampe> hippo = dynamic_pointer_cast<Hippocampe>(entity);

				if (hippo->getHitBox().intersects(player->getHitBox())) {
					player->takeDamage(1, hud);
					hpToRemove = 1;

				}
				if (hippo->animClock.getElapsedTime().asSeconds() >= hippoFrame)
				{
					hippo->animClock.restart();
					anim.continueAnimation(hippo->entitySprite);
				}
				if (hippo->animPlayed)
				{
					if (hippo->entitySprite.getTexture() != &text.hippocampesShootText)
					{
						hippo->entitySprite.setTexture(text.hippocampesShootText);
						hippo->entitySprite.setTextureRect(IntRect(0, 0, hippo->entitySprite.getTextureRect().height, hippo->entitySprite.getTextureRect().height));
						hippoFrame = 0.2f;
					}
				}
				else if (hippo->entitySprite.getTexture() != &text.hippocampesText)
				{
					hippo->entitySprite.setTexture(text.hippocampesText);
					hippo->entitySprite.setTextureRect(IntRect(0, 0, hippo->entitySprite.getTextureRect().height, hippo->entitySprite.getTextureRect().height));
					hippoFrame = 0.3f;
				}
			}

			else if (entity->entityType == "BulletHippo")
			{
				shared_ptr<BulletHippocampe> bullet = dynamic_pointer_cast<BulletHippocampe>(entity);

				bullet->move();
				if (bullet->getHitBox().intersects(player->getHitBox())) {
					manager->deleteEntity(entity);
					player->takeDamage(1, hud);
					hpToRemove = 1;
				}

				if (player->getCamera()->getCenter().x - bulletdistancetocentercameratodie > bullet->entitySprite.getPosition().x || player->getCamera()->getCenter().x + bulletdistancetocentercameratodie < bullet->entitySprite.getPosition().x)
				{
					manager->deleteEntity(entity);
				}
			}

			else if (entity->entityType == "PoissonGlobe")
			{
				shared_ptr<PoissonGlobe> pG = dynamic_pointer_cast<PoissonGlobe>(entity);

				if (pG->getHitBox().intersects(player->getHitBox())) {
					player->takeDamage(1, hud);
					pG->grow();
					pG->pushPlayer(player);
				}

				if (pG->animClock.getElapsedTime().asSeconds() >= poissonGFrame)
				{
					pG->animClock.restart();
					anim.continueAnimation(pG->entitySprite);
				}
				if (!pG->getIsGrown())
				{
					if (pG->entitySprite.getTexture() != &text.poissonGlobeIdleText)
					{
						pG->entitySprite.setTexture(text.poissonGlobeIdleText);
						pG->entitySprite.setTextureRect(IntRect(0, 0, pG->entitySprite.getTextureRect().height, pG->entitySprite.getTextureRect().height));
						poissonGFrame = 0.2f;
					}
				}
				else if (pG->entitySprite.getTexture() != &text.poissonGlobeGrownText)
				{
					pG->entitySprite.setTexture(text.poissonGlobeGrownText);
					pG->entitySprite.setTextureRect(IntRect(0, 0, pG->entitySprite.getTextureRect().height, pG->entitySprite.getTextureRect().height));
					poissonGFrame = 0.3f;
				}
			}

			else if (entity->entityType == "MiniMeduse")
			{
				shared_ptr<MiniMeduse> miniM = dynamic_pointer_cast<MiniMeduse>(entity);

				if (miniM->animClock.getElapsedTime().asSeconds() >= miniM->miniMFrame)
				{
					miniM->animClock.restart();
					anim.continueAnimation(miniM->entitySprite);
				}
				if (miniM->getHitBox().intersects(player->getHitBox())) {
					player->takeDamage(1, hud);
					hpToRemove = 1;
				}

				if (miniM->getHitBox().intersects(player->getHitBox()))
				{
					player->setHealth(player->getHealth() - 1);
					manager->deleteEntity(entity);
				}

				else if (miniM->entitySprite.getPosition().x <= -20 || miniM->getHealth() <= 0) { manager->deleteEntity(entity); }

			}

			else if (entity->entityType == "Laser")
			{
				shared_ptr<Laser> laser = dynamic_pointer_cast<Laser>(entity);

				if (laser->getHitBox().intersects(player->getHitBox())) {
					player->takeDamage(1, hud);
					hpToRemove = 1;
				}

				if (laser->delClock.getElapsedTime().asSeconds() > 0.2f)
				{
					laser->delClock.restart();
					manager->deleteEntity(entity);
				}
			}

			else if (entity->entityType == "WarningLaser")
			{
				shared_ptr<WarningLaser> wlaser = dynamic_pointer_cast<WarningLaser>(entity);

				if (wlaser->animClock.getElapsedTime().asSeconds() >= wlaser->wLaserFrame)
				{
					wlaser->animClock.restart();
					anim.continueAnimation(wlaser->entitySprite);
				}
				if (wlaser->tempClock.getElapsedTime().asSeconds() <= 2.f)
				{
					wlaser->delClock.restart();
					wlaser->setSpawned(true);
				}
				else if (!wlaser->shooted && wlaser->getSpawned() && wlaser->entitySprite.getTexture() != &text.tentacleLaserBefoShootText)
				{
					wlaser->delClock.restart();
					wlaser->entitySprite.setTexture(text.tentacleLaserBefoShootText);
					wlaser->entitySprite.setTextureRect(IntRect(0, 0, wlaser->entitySprite.getTextureRect().height, wlaser->entitySprite.getTextureRect().height));
					wlaser->wLaserFrame = 0.1f;
				}
				if (wlaser->shooted && wlaser->entitySprite.getTexture() != &text.tentacleLaserUnSpawnText)
				{
					wlaser->entitySprite.setTexture(text.tentacleLaserUnSpawnText);
					wlaser->entitySprite.setTextureRect(IntRect(0, 0, wlaser->entitySprite.getTextureRect().height, wlaser->entitySprite.getTextureRect().height));
					wlaser->wLaserFrame = 0.2f;
				}
				if (wlaser->delClock.getElapsedTime().asSeconds() >= 2.4f)
				{
					manager->deleteEntity(entity);
				}
			}

			else if (entity->entityType == "Money")
			{
				shared_ptr<Money> money = dynamic_pointer_cast<Money>(entity);

				if (money->getHitBox().intersects(player->getHitBox()))
				{
					player->setMoney(player->getMoney() + 1,hud); // add money in score
					hud->addPlayerMoney(player->getMoney());
					manager->deleteEntity(entity);
				}
			}

			else if (entity->entityType == "Medusa")
			{
				shared_ptr<Medusa> medusa = dynamic_pointer_cast<Medusa>(entity);

				if (medusa->getHitBox().intersects(player->getHitBox())) {
					player->takeDamage(1, hud);
				}

				if (medusa->animClock.getElapsedTime().asSeconds() >= medusa->medusaFrame)
				{
					medusa->animClock.restart();
					anim.continueAnimation(medusa->entitySprite);
				}
				if (medusa->getPhase3State() && medusa->entitySprite.getTexture() != &text.medusaPhase3Text)
				{
					medusa->entitySprite.setTexture(text.medusaPhase3Text);
					medusa->entitySprite.setTextureRect(IntRect(0, 0, medusa->entitySprite.getTextureRect().height, medusa->entitySprite.getTextureRect().height));
				}
				else if (medusa->getPhase2State() && medusa->entitySprite.getTexture() != &text.medusaPhase2Text)
				{
					medusa->entitySprite.setTexture(text.medusaPhase2Text);
					medusa->entitySprite.setTextureRect(IntRect(0, 0, medusa->entitySprite.getTextureRect().height, medusa->entitySprite.getTextureRect().height));
				}
				else if (medusa->getPhase1State() && medusa->entitySprite.getTexture() != &text.medusaPhase1Text)
				{
					medusa->entitySprite.setTexture(text.medusaPhase1Text);
					medusa->entitySprite.setTextureRect(IntRect(0, 0, medusa->entitySprite.getTextureRect().height, medusa->entitySprite.getTextureRect().height));
				}
			}

			else if (entity->entityType == "JellyFishGenerator")
			{
				shared_ptr<JellyFishGenerator> jfg = dynamic_pointer_cast<JellyFishGenerator>(entity);

				if (jfg->getHitBox().intersects(player->getHitBox())) {
					player->takeDamage(1, hud);
				} 

				if (jfg->animClock.getElapsedTime().asSeconds() >= jfg->jellyFishGenFrame)
				{
					jfg->animClock.restart();
					anim.continueAnimation(jfg->entitySprite);
				}
				if (jfg->tempClock.getElapsedTime().asSeconds() <= 1.f )
				{
					jfg->setSpawned(true);
				}
				else if (jfg->getSpawned() && jfg->entitySprite.getTexture() != &text.tentacleJFGSummonText)
				{
					jfg->entitySprite.setTexture(text.tentacleJFGSummonText);
					jfg->entitySprite.setTextureRect(IntRect(0, 0, jfg->entitySprite.getTextureRect().height, jfg->entitySprite.getTextureRect().height));
					jfg->jellyFishGenFrame = 0.1f;
				}
			}

			else if (entity->entityType == "Tentacle")
			{
				shared_ptr<Tentacle> tentacle = dynamic_pointer_cast<Tentacle>(entity);

				if (tentacle->getHitBox().intersects(player->getHitBox())) {
					player->takeDamage(1, hud);
				}

				if (tentacle->getHitBox().intersects(player->getHitBox())) {
					player->takeDamage(1,hud);
				}

				if (tentacle->animClock.getElapsedTime().asSeconds() >= tentacle->tentacleFrame)
				{
					tentacle->animClock.restart();
					anim.continueAnimation(tentacle->entitySprite);
				}

				if (tentacle->getTentacleType() == "AttackRise")
				{
					if (tentacle->entitySprite.getTexture() != &text.tentacleAttackRiseText && !tentacle->tentacleRised)
					{
						tentacle->entitySprite.setTexture(text.tentacleAttackRiseText);
						tentacle->entitySprite.setTextureRect(IntRect(0, 0, tentacle->entitySprite.getTextureRect().height, tentacle->entitySprite.getTextureRect().height));
						tentacle->tentacleFrame = 0.14f;
						tentacle->tentacleRised = true;
					}
					if (tentacle->entitySprite.getTexture() != &text.tentacleAttackIdleRiseText && tentacle->waitClock.getElapsedTime().asSeconds() >= 1.26f && !tentacle->tentacleRised2)
					{
						tentacle->entitySprite.setTexture(text.tentacleAttackIdleRiseText);
						tentacle->entitySprite.setTextureRect(IntRect(0, 0, tentacle->entitySprite.getTextureRect().height, tentacle->entitySprite.getTextureRect().height));
						tentacle->tentacleFrame = 0.14f;
						tentacle->tentacleRised2 = true;
					}
					if (tentacle->entitySprite.getTexture() != &text.tentacleAttackUnRiseText && tentacle->waitClock.getElapsedTime().asSeconds() >= 2.52f)
					{
						tentacle->entitySprite.setTexture(text.tentacleAttackUnRiseText);
						tentacle->entitySprite.setTextureRect(IntRect(0, 0, tentacle->entitySprite.getTextureRect().height, tentacle->entitySprite.getTextureRect().height));
						tentacle->tentacleFrame = 0.14f;
					}
					if (tentacle->waitClock.getElapsedTime().asSeconds() >= 3.6f)
					{
						manager->deleteEntity(entity);
					}
				}
				if (tentacle->getTentacleType() == "Attack")
				{
					tentacle->tentacleFrame = 0.06f;
					if (tentacle->waitClock.getElapsedTime().asSeconds() >= 0.72f)
					{
						manager->deleteEntity(entity);
					}
				}
			}
		}

		for (int i = 0; i < manager->getAllEnnemies().size(); i++)
		{
			shared_ptr<Entity> e = manager->getAllEnnemies()[i];
			shared_ptr<Enemy> enemy = dynamic_pointer_cast<Enemy>(e);

			enemy->pattern(manager);
		}
		managerMutex.unlock();
	}
}

void InGameManagement::hudAnim(HUD* hud, int i) {
	if (hud->animClock.getElapsedTime().asSeconds() >= 0.1) {
		hud->animClock.restart();
		if (!hud->isAnimDone) {
			switch (i) {
			case 1:
				if (anim.continueAnimation(hud->playerHP[0]) == 1)
				{
					hud->isAnimDone = true;
					for (int j = 0; j < i; j++) {
						hud->playerHP.erase(hud->playerHP.begin());
					}
				}
				break;
			case 2:
				if (anim.continueAnimation(hud->playerHP[0]) == 1 and anim.continueAnimation(hud->playerHP[1]) == 1){
					hud->isAnimDone = true;
					for (int j = 0; j < i; j++) {
						hud->playerHP.erase(hud->playerHP.begin());
					}
				}
				break;
			case 3:
				if (anim.continueAnimation(hud->playerHP[0]) == 1 and anim.continueAnimation(hud->playerHP[1]) == 1 and anim.continueAnimation(hud->playerHP[2]) == 1){
					hud->isAnimDone = true;
					for (int j = 0; j < i; j++) {
						hud->playerHP.erase(hud->playerHP.begin());
					}
				}
				break;
			}
		}
	}
}

void InGameManagement::healAnim(HUD* hud) {
	if (hud->healClock.getElapsedTime().asSeconds() >= 0.1) {
		hud->healClock.restart();
		if (isUpdateHP) {
			if (anim.continueAnimation(hud->playerHP.front())==1)
			{
				isUpdateHP = false;				
			}
		}
	}
}