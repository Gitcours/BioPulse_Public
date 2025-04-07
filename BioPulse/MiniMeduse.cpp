#include "MiniMeduse.h"

MiniMeduse::MiniMeduse(Vector2f _pos, Texture& _text, float _speed, int _hp) : Enemy(_pos, _text, _speed, _hp)
{
    mt19937 gen(rd());
    uniform_int_distribution<> positionGoal(7 * 32, 21 * 32);
    int goal = positionGoal(gen);
    waypoints.push_back(Vector2i(entitySprite.getPosition().x - 50, goal));
    waypoints.push_back(Vector2i(-50, goal));
	entityType = "MiniMeduse";
}

FloatRect MiniMeduse::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x + 2, boundsPos.y + 5, boundsSize.x - 3, boundsSize.y / 3.f * 2);
}

void MiniMeduse::move() 
{
    Vector2i target = waypoints[currentWaypoint];
    Vector2f directionMiniMeduse = Vector2f(target) - entitySprite.getPosition();
    float distance = sqrt(directionMiniMeduse.x * directionMiniMeduse.x + directionMiniMeduse.y * directionMiniMeduse.y);

    if (distance < 2.0f) {
        if (currentWaypoint >= waypoints.size() - 1)
        {
            currentWaypoint = -1;
        }
        currentWaypoint += 1;
    }
    else
    {
        directionMiniMeduse /= distance;
        position = entitySprite.getPosition() + directionMiniMeduse * speed * timePassed;
        entitySprite.setPosition(position);
    }
}

void MiniMeduse::pattern(EntityManager* manager)
{
    move();
}
