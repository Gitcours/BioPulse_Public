#pragma once
#include "Enemy.h"
#include "Player.h"
class PoissonGlobe :
public Enemy
{
public:
    PoissonGlobe(Vector2f _pos, Texture& _text, float _speed, int _hp, string _facing);

    FloatRect getHitBox() override;
	void move() override;
    void pattern(EntityManager* manager) override;
    void grow();
    void shrink();
    void pushPlayer(shared_ptr<Player> player);
    bool checkCollision(shared_ptr<Player> player);
    void update(shared_ptr<Player> player);

    bool getIsGrown() const;

private:
    Clock growClock;
    bool isGrown = false;
    string facing;

};

