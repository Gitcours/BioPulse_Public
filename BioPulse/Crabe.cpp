#include "Crabe.h"

Crabe::Crabe(Vector2f _pos, Texture& _text, float _speed, int _hp, int w1, int w2)
    : waypoint1(w1), waypoint2(w2), Enemy(_pos, _text, _speed, _hp), movingRight(true)  
{
    entityType = "Crabe";
    entitySprite.setOrigin(Vector2f(entityText.getSize().y / 2.f, entityText.getSize().y / 2.f));
}

FloatRect Crabe::getHitBox()
{
    Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
    Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
    return FloatRect(boundsPos.x + 0, boundsPos.y + boundsSize.y / 2.f, boundsSize.x, boundsSize.y / 2.f);
}


void Crabe::move()
{
    float movement = speed * timePassed;

    if (movingRight) {
        entitySprite.move(movement, 0);
        entitySprite.setScale(1, 1);
    }
    else {
        entitySprite.move(-movement, 0);
		entitySprite.setScale(-1, 1);
    }

    if (entitySprite.getPosition().x >= waypoint2) {
        movingRight = false;
    }
    if (entitySprite.getPosition().x <= waypoint1) {
        movingRight = true;
    }
}

void Crabe::pattern(EntityManager* manager)
{
    move();
}



