#include "Medusa.h"
#include "EntityManager.h"
#include "TextureManager.h"

Medusa::Medusa(Vector2f _pos, Texture& _text, float _speed, int _hp) : Enemy(_pos, _text, _speed, _hp) 
{ 
	entityType = "Medusa";
	entitySprite.setScale(5.f, 5.f);
	manager->createTentacle(Vector2f(entitySprite.getPosition().x + entitySprite.getGlobalBounds().width / 3, entitySprite.getPosition().y + entitySprite.getGlobalBounds().height + 25), text.tentacleAttackIdleText, 1, "DECO");
	manager->createTentacle(Vector2f(entitySprite.getPosition().x, entitySprite.getPosition().y + entitySprite.getGlobalBounds().height + 25), text.tentacleJellyFishGenIdleText, 1, "DECO");
	manager->createTentacle(Vector2f(entitySprite.getPosition().x - entitySprite.getGlobalBounds().width / 3, entitySprite.getPosition().y + entitySprite.getGlobalBounds().height + 25), text.tentacleLaserIdleText, 1, "DECO");
}

FloatRect Medusa::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x, boundsPos.y + 50, boundsSize.x, boundsSize.y + 50);
}

void Medusa::move() {}

void Medusa::setWarningLaser(EntityManager* manager) 
{
	shared_ptr<Entity> ePlayer = manager->getAllPlayers()[0];
	shared_ptr<Player> player = dynamic_pointer_cast<Player>(ePlayer);
	
	int distance1 = abs(player->entitySprite.getPosition().y - 6 * 32);
	int distance2 = abs(player->entitySprite.getPosition().y - 9 * 32); 
	int distance3 = abs(player->entitySprite.getPosition().y - 14 * 32);

	if (distance1 < distance2 && distance1 < distance3) { laserSpawnPosY = 6 * 32; }
	else if (distance2 < distance1 && distance2 < distance3) { laserSpawnPosY = 9 * 32; }
	else if (distance3 < distance1 && distance3 < distance2) { laserSpawnPosY = 14 * 32; }
		
	warningLaserPos.push_back(laserSpawnPosY);
	manager->createWarningLaser(Vector2f(entitySprite.getPosition().x - 450, warningLaserPos[0]), text.tentacleLaserSpawnText, 1);
}

void Medusa::attackLaser(EntityManager* manager)
{
	for (int i = 0; i < manager->getAllWarningLasers().size(); i++)
	{
		shared_ptr<Entity> entity = manager->getAllWarningLasers()[i];
		shared_ptr<WarningLaser> wlaser = dynamic_pointer_cast<WarningLaser>(entity);

		wlaser->shooted = true;
	}
	manager->createLaser(Vector2f(0, warningLaserPos[0] - 200), text.laserText, 1);
	warningLaserPos.clear();
}

void Medusa::attackSummon(EntityManager* manager)
{
	mt19937 gen(rd2());
	uniform_int_distribution<> positionGoal(600, 750);
	int goal = positionGoal(gen);
	manager->createJellyFishGenerator(Vector2f(entitySprite.getPosition().x - 150, goal), text.tentacleJFGSpawnText, 0.f, 10);
}

void Medusa::attackTentacle(EntityManager* manager)
{
	shared_ptr<Entity> ePlayer = manager->getAllPlayers()[0];
	shared_ptr<Player> player = dynamic_pointer_cast<Player>(ePlayer);

	cout << endl << player->entitySprite.getPosition().x << " / " << player->entitySprite.getPosition().y << endl;

	int distance1 = sqrt(pow(player->entitySprite.getPosition().x - 553, 2) + sqrt(pow(player->entitySprite.getPosition().y - 480, 2)));
	int distance2 = sqrt(pow(player->entitySprite.getPosition().x - 855, 2) + sqrt(pow(player->entitySprite.getPosition().y - 320, 2)));
	int distance3 = sqrt(pow(player->entitySprite.getPosition().x - 233, 2) + sqrt(pow(player->entitySprite.getPosition().y - 224, 2)));

	if (distance1 < distance2 && distance1 < distance3) { tentaculeSpawnX = 553; tentaculeSpawnY = 0; }
	else if (distance2 < distance1 && distance2 < distance3) { tentaculeSpawnX = 855; tentaculeSpawnY = 0; }
	else if (distance3 < distance1 && distance3 < distance2) { tentaculeSpawnX = 233; tentaculeSpawnY = -90; }

	manager->createTentacle(Vector2f(tentaculeSpawnX, tentaculeSpawnY), text.tentacleAttackText, 1, "Attack");
}

void Medusa::pattern(EntityManager* manager) 
{
	cout << manager->getAllJellyFishGenerators().size() << endl<< warningClock.getElapsedTime().asSeconds() << endl;
	//cout << phase1;
	//cout << phase2;
	//cout << phase3;
	if (phase1 && manager->getAllJellyFishGenerators().empty())
	{
		if (warningClock.getElapsedTime().asSeconds() > 8.f && manager->getAllLasers().empty()) {
			warningClock.restart();
			setWarningLaser(manager);
		}

		if (laserClock.getElapsedTime().asSeconds() > 11.f && !manager->getAllWarningLasers().empty()) {
			warningClock.restart();
			laserClock.restart();
			attackLaser(manager);
		}
		if (getHealth() <= getHealth() / 3 * 2)
		{
			phase2 = true;
		}

	}

	if (phase2)
	{
		if (medusaAttackSummonClock.getElapsedTime().asSeconds() > 20.f && manager->getAllJellyFishGenerators().empty() && manager->getAllWarningLasers().empty()) {
			medusaAttackSummonClock.restart();
			attackSummon(manager);
		}
		if (getHealth() <= getHealth() / 3)
		{
			phase3 = true;
		}
	}

	if (phase3)
	{
		if (medusaAttackTentacleClock.getElapsedTime().asSeconds() > 10.f && manager->getAllJellyFishGenerators().empty())
		{
			if (!tentRised)
			{
				manager->createTentacle(Vector2f(entitySprite.getPosition().x, entitySprite.getPosition().y - 400), text.tentacleAttackRiseText, 1, "AttackRise");
				tentRised = true;
			}
		}
		if (medusaAttackTentacleClock.getElapsedTime().asSeconds() > 11.5f && manager->getAllJellyFishGenerators().empty())
		{
			medusaAttackTentacleClock.restart();
			tentRised = false;
			attackTentacle(manager);
		}
	}

}

bool Medusa::getPhase1State() const { return phase1; }
bool Medusa::getPhase2State() const { return phase2; }
bool Medusa::getPhase3State() const { return phase3; }