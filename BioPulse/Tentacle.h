#pragma once
#include "Entity.h"
class Tentacle :
    public Entity
{
private :
    string tentacleType;

public :
    Clock waitClock;
    float tentacleFrame = 0.1f;
    bool tentacleRised = false;
    bool tentacleRised2 = false;


    Tentacle(Vector2f _pos, Texture& _text, int _hp, string _type);

    FloatRect getHitBox() override;

    string getTentacleType() const;
};

