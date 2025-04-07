#pragma once
#include "Outils.h"
#include "Player.h"
#include "Money.h"
#include "Crabe.h"
#include "PoissonGlobe.h"
#include "Medusa.h"
#include "JellyFishGenerator.h"
#include "MiniMeduse.h"
#include "WarningLaser.h"
#include "Laser.h"
#include "Projectiles.h"
#include "Pet.h"
#include "Hippocampe.h"
#include "BulletHippocampe.h"
#include "Tentacle.h"

class EntityManager
{
private:
    static EntityManager* instance;
    EntityManager() {}

    vector<shared_ptr<Entity>> allPlayers;
	vector<shared_ptr<Entity>> allplayerprojectiles;
	vector<shared_ptr<Entity>> allPets;
	vector<shared_ptr<Entity>> allMoney;

    vector<shared_ptr<Entity>> allCrabes;
    vector<shared_ptr<Entity>> allPoissonGlobes;
	vector<shared_ptr<Entity>> allHippocampes;
	vector<shared_ptr<Entity>> allHippoBullets;
	vector<shared_ptr<Entity>> allMedusa;
	vector<shared_ptr<Entity>> allJellyFishGenerator;
	vector<shared_ptr<Entity>> allMiniMeduse;
	vector<shared_ptr<Entity>> allWarnignLaser;
	vector<shared_ptr<Entity>> allLasers;
	vector<shared_ptr<Entity>> allTentacles;

    vector<shared_ptr<Entity>> allEnnemies;
    vector<shared_ptr<Entity>> allEntities;


public:
    static EntityManager* getInstance();
    ~EntityManager();
    void createPlayerProjectiles(Vector2f _pos, Texture& _text, string _direction);
    void createPlayer(Vector2f _pos, Texture& _textPlayer, Texture& _textPlayerJumpEffect, Texture& _textPlayerLandEffect, float _speed, int _hp);
    void createPet(Vector2f _pos, Texture& _text);

    void createCrabe(Vector2f _pos, Texture& _text, float _speed, int _hp, int w1, int w2);
    void createPoissonGlobe(Vector2f _pos, Texture& _text, float _speed, int _hp, string _facing);
    void createHippocampe(Vector2f _pos, Texture& _text, float speed, int _hp, string _facing);
	void createBulletHippocampe(Vector2f _pos, Texture& _text,int _hp, float _speed, string _direction);
    void createMedusa(Vector2f _pos, Texture& _text, float _speed, int _hp);
    void createJellyFishGenerator(Vector2f _pos, Texture& _text, float _speed, int _hp);
    void createMiniMeduse(Vector2f _pos, Texture& _text, float _speed, int _hp);

    void createWarningLaser(Vector2f _pos, Texture& _text, int _hp);
    void createLaser(Vector2f _pos, Texture& _text, int _hp);
    void createTentacle(Vector2f _pos, Texture& _text, int _hp, string _type);
	void createMoney(Vector2f _pos, Texture& _text, int _hp);

    void deleteEntity(shared_ptr<Entity> entity);

    vector<shared_ptr<Entity>> getAllPlayers() const;
	vector<shared_ptr<Entity>> getAllPlayerProjectiles() const;
	vector<shared_ptr<Entity>> getAllPets() const;
	vector<shared_ptr<Entity>> getAllMoney() const;

    vector<shared_ptr<Entity>> getAllCrabes() const;
    vector<shared_ptr<Entity>> getAllPoissonGlobes() const;
	vector<shared_ptr<Entity>> getAllHippocampes() const;
	vector<shared_ptr<Entity>> getAllHippoBullets() const;
	vector<shared_ptr<Entity>> getAllMedusas() const;
	vector<shared_ptr<Entity>> getAllJellyFishGenerators() const;
	vector<shared_ptr<Entity>> getAllMiniMeduses() const;
	vector<shared_ptr<Entity>> getAllWarningLasers() const;
	vector<shared_ptr<Entity>> getAllLasers() const;
	vector<shared_ptr<Entity>> getAllTentacles() const;

	vector<shared_ptr<Entity>> getAllEnnemies() const;
	vector<shared_ptr<Entity>> getAllEntities() const;
};

extern EntityManager* manager;
