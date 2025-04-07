#pragma once
#include "Entity.h"

class BulletHippocampe : public Entity {
private :
	string direction;
	float speed;

public:
    BulletHippocampe(Vector2f _pos, Texture& _text, int _hp, float _speed, string _direction);
    void move();
    FloatRect getHitBox() override;
};