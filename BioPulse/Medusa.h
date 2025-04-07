#pragma once
#include "Enemy.h"

class TextureManager;

class Medusa :
    public Enemy
{ 
private:
    Clock warningClock;
    Clock laserClock;
	Clock medusaAttackSummonClock;
    Clock medusaAttackTentacleClock;

	int laserSpawnPosY;
    int tentaculeSpawnX;
    int tentaculeSpawnY;

    bool tentRised = false;
    bool phase1 = true;
    bool phase2 = true;
    bool phase3 = true;

	vector<int> warningLaserPos;

    random_device rd2;

public:
    float medusaFrame = 0.3f;

    Medusa(Vector2f _pos, Texture& _text, float _speed, int _hp);

    FloatRect getHitBox() override;

    void move() override;
    void pattern(EntityManager* manager) override;

    void attackSummon(EntityManager* manager);
	void setWarningLaser(EntityManager* manager);
	void attackLaser(EntityManager* manager);
    void attackTentacle(EntityManager* manager);

    bool getPhase1State() const;
    bool getPhase2State() const;
    bool getPhase3State() const;
};

