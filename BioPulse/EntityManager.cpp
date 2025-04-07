#include "EntityManager.h"

EntityManager* EntityManager::getInstance()
{
	if (instance == nullptr) { instance = new EntityManager(); }
	return instance;
}

EntityManager::~EntityManager()
{
	allPlayers.clear();
	allPets.clear();
	allplayerprojectiles.clear();
	allWarnignLaser.clear();
	allLasers.clear();
	allTentacles.clear();
	allMoney.clear();

	allCrabes.clear();
	allPoissonGlobes.clear();
	allHippocampes.clear();
	allHippoBullets.clear();
	allMedusa.clear();
	allJellyFishGenerator.clear();
	allMiniMeduse.clear();

	allEnnemies.clear();
	allEntities.clear();
}
void EntityManager::createPlayer(Vector2f _pos, Texture& _textPlayer, Texture& _textPlayerJumpEffect, Texture& _textPlayerLandEffect, float _speed, int _hp)
{
	shared_ptr<Player> p = make_shared<Player>(_pos, _textPlayer, _textPlayerJumpEffect, _textPlayerLandEffect, _speed, _hp);
	allPlayers.push_back(p);
	allEntities.push_back(p);
}

void EntityManager::createPet(Vector2f _pos, Texture& _text) { 
	shared_ptr<Pet> p = make_shared<Pet>(_pos, _text);
	allPets.push_back(p);
	allEntities.push_back(p);
}

void EntityManager::createPlayerProjectiles(Vector2f _pos, Texture& _text, std::string _direction)
{
	shared_ptr<Projectiles> pr = make_shared<Projectiles>(_pos, _text, _direction);
	allplayerprojectiles.push_back(pr);
	allEntities.push_back(pr);
}

void EntityManager::createWarningLaser(Vector2f _pos, Texture& _text, int _hp)
{
	shared_ptr<WarningLaser> p = make_shared<WarningLaser>(_pos, _text, _hp);
	allWarnignLaser.push_back(p);
	allEntities.push_back(p);
}

void EntityManager::createLaser(Vector2f _pos, Texture& _text, int _hp)
{
	shared_ptr<Laser> p = make_shared<Laser>(_pos, _text, _hp);
	allLasers.push_back(p);
	allEntities.push_back(p);
}

void EntityManager::createTentacle(Vector2f _pos, Texture& _text, int _hp, string _type)
{
	shared_ptr<Tentacle> p = make_shared<Tentacle>(_pos, _text, _hp, _type);
	allTentacles.push_back(p);
	allEntities.push_back(p);
}

void EntityManager::createMoney(Vector2f _pos, Texture& _text, int _hp)
{
	shared_ptr<Money> p = make_shared<Money>(_pos, _text, _hp);
	allMoney.push_back(p);
	allEntities.push_back(p);
}

// ENNEMIES


void EntityManager::createCrabe(Vector2f _pos, Texture& _text, float _speed, int _hp, int w1, int w2)
{
	shared_ptr<Crabe> c = make_shared<Crabe>(_pos, _text, _speed, _hp, w1, w2);
	allCrabes.push_back(c);
	allEnnemies.push_back(c);
	allEntities.push_back(c);
}

void EntityManager::createPoissonGlobe(Vector2f _pos, Texture& _text, float _speed, int _hp, string _facing)
{
	shared_ptr<PoissonGlobe> g = make_shared<PoissonGlobe>(_pos, _text, _speed, _hp, _facing);
	allPoissonGlobes.push_back(g);
	allEnnemies.push_back(g);
	allEntities.push_back(g);
}

void EntityManager::createHippocampe(Vector2f _pos, Texture& _text, float _speed, int _hp, string _facing)
{
	shared_ptr<Hippocampe> g = make_shared<Hippocampe>(_pos, _text, _speed, _hp, _facing);
	allHippocampes.push_back(g);
	allEnnemies.push_back(g);
	allEntities.push_back(g);
}

void EntityManager::createBulletHippocampe(Vector2f _pos, Texture& _text, int _hp,  float _speed, string _direction)
{
	shared_ptr<BulletHippocampe> g = make_shared<BulletHippocampe>(_pos, _text, _hp, _speed, _direction);
	allHippoBullets.push_back(g);
	allEntities.push_back(g);
}

void EntityManager::createMedusa(Vector2f _pos, Texture& _text, float _speed, int _hp)
{
	shared_ptr<Medusa> p = make_shared<Medusa>(_pos, _text, _speed, _hp);
	allMedusa.push_back(p);
	allEnnemies.push_back(p);
	allEntities.push_back(p);
}

void EntityManager::createJellyFishGenerator(Vector2f _pos, Texture& _text, float _speed, int _hp)
{
	shared_ptr<JellyFishGenerator> p = make_shared<JellyFishGenerator>(_pos, _text, _speed, _hp);
	allJellyFishGenerator.push_back(p);
	allEnnemies.push_back(p);
	allEntities.push_back(p);
}

void EntityManager::createMiniMeduse(Vector2f _pos, Texture& _text, float _speed, int _hp)
{
	shared_ptr<MiniMeduse> p = make_shared<MiniMeduse>(_pos, _text, _speed, _hp);
	allMiniMeduse.push_back(p);
	allEnnemies.push_back(p);
	allEntities.push_back(p);
}

// ENNEMIES


void EntityManager::deleteEntity(shared_ptr<Entity> entity) {
	if (entity->entityType == "Player")
	{
		int i = 0;
		for (auto& e : allPlayers)
		{
			if (e == entity) { allPlayers.erase(allPlayers.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "Pet")
	{
		int i = 0;
		for (auto& e : allPets)
		{
			if (e == entity) { allPets.erase(allPets.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "Projectiles")
	{
		int i = 0;
		for (auto& e : allplayerprojectiles)
		{
			if (e == entity) { allplayerprojectiles.erase(allplayerprojectiles.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "WarningLaser")
	{
		int i = 0;
		for (auto& e : allWarnignLaser)
		{
			if (e == entity) { allWarnignLaser.erase(allWarnignLaser.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "Laser")
	{
		int i = 0;
		for (auto& e : allLasers)
		{
			if (e == entity) { allLasers.erase(allLasers.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "Tentacle")
	{
		int i = 0;
		for (auto& e : allTentacles)
		{
			if (e == entity) { allTentacles.erase(allTentacles.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "Money")
	{
		int i = 0;
		for (auto& e : allMoney)
		{
			if (e == entity) { allMoney.erase(allMoney.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}

	else if (entity->entityType == "Crabe")
	{
		int i = 0;
		for (auto& e : allCrabes)
		{
			if (e == entity) { allCrabes.erase(allCrabes.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEnnemies)
		{
			if (e == entity) { allEnnemies.erase(allEnnemies.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "PoissonGlobe")
	{
		int i = 0;
		for (auto& e : allPoissonGlobes)
		{
			if (e == entity) { allPoissonGlobes.erase(allPoissonGlobes.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEnnemies)
		{
			if (e == entity) { allEnnemies.erase(allEnnemies.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "Hippocampe")
	{
		int i = 0;
		for (auto& e : allHippocampes)
		{
			if (e == entity) { allHippocampes.erase(allHippocampes.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEnnemies)
		{
			if (e == entity) { allEnnemies.erase(allEnnemies.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "BulletHippo")
	{
		int i = 0;
		for (auto& e : allHippoBullets)
		{
			if (e == entity) { allHippoBullets.erase(allHippoBullets.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "Medusa")
	{
		int i = 0;
		for (auto& e : allMedusa)
		{
			if (e == entity) { allMedusa.erase(allMedusa.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEnnemies)
		{
			if (e == entity) { allEnnemies.erase(allEnnemies.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "JellyFishGenerator")
	{
		int i = 0;
		for (auto& e : allJellyFishGenerator)
		{
			if (e == entity) { allJellyFishGenerator.erase(allJellyFishGenerator.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEnnemies)
		{
			if (e == entity) { allEnnemies.erase(allEnnemies.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
	}
	else if (entity->entityType == "MiniMeduse")
	{
		int i = 0;
		for (auto& e : allEntities)
		{
			if (e == entity) { allEntities.erase(allEntities.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allEnnemies)
		{
			if (e == entity) { allEnnemies.erase(allEnnemies.begin() + i); break; } i++;
		}
		i = 0;
		for (auto& e : allMiniMeduse)
		{
			if (e == entity) { allMiniMeduse.erase(allMiniMeduse.begin() + i); break; } i++;
		}
	}

}

vector<shared_ptr<Entity>> EntityManager::getAllPlayers() const { return allPlayers; }
vector<shared_ptr<Entity>> EntityManager::getAllPlayerProjectiles() const { return allplayerprojectiles; }
vector<shared_ptr<Entity>> EntityManager::getAllPets() const { return allPets; }
vector<shared_ptr<Entity>> EntityManager::getAllMoney() const { return allMoney; }

vector<shared_ptr<Entity>> EntityManager::getAllCrabes() const { return allCrabes; }
vector<shared_ptr<Entity>> EntityManager::getAllPoissonGlobes() const { return allPoissonGlobes; }
vector<shared_ptr<Entity>> EntityManager::getAllHippocampes() const { return allHippocampes; }
vector<shared_ptr<Entity>> EntityManager::getAllHippoBullets() const { return allHippoBullets; }
vector<shared_ptr<Entity>> EntityManager::getAllMedusas() const { return allMedusa; }
vector<shared_ptr<Entity>> EntityManager::getAllJellyFishGenerators() const { return allJellyFishGenerator; }
vector<shared_ptr<Entity>> EntityManager::getAllMiniMeduses() const { return allMiniMeduse; }
vector<shared_ptr<Entity>> EntityManager::getAllWarningLasers() const { return allWarnignLaser; }
vector<shared_ptr<Entity>> EntityManager::getAllLasers() const { return allLasers; }
vector<shared_ptr<Entity>> EntityManager::getAllTentacles() const { return allTentacles; }

vector<shared_ptr<Entity>> EntityManager::getAllEnnemies() const { return allEnnemies; }
vector<shared_ptr<Entity>> EntityManager::getAllEntities() const { return allEntities; }

EntityManager* EntityManager::instance = nullptr;
EntityManager* manager = EntityManager::getInstance();