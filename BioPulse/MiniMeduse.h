#pragma once
#include "Enemy.h"
#include "random"

class MiniMeduse :
    public Enemy
{
private :
    Vector2f position;
    vector<Vector2i> waypoints;
    random_device rd;

    int currentWaypoint = 0;

public:
    float miniMFrame = 0.2f;

    MiniMeduse(Vector2f _pos, Texture& _text, float _speed, int _hp);

    FloatRect getHitBox() override;
    void move() override;
    void pattern(EntityManager* manager) override;
};

