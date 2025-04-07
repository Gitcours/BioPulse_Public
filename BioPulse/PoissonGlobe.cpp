#include "PoissonGlobe.h"
#include "EntityManager.h"
PoissonGlobe::PoissonGlobe(Vector2f _pos, Texture& _text, float _speed, int _hp, string _facing) : facing(_facing), Enemy(_pos, _text, _speed, _hp) {
	entityType = "PoissonGlobe";
    if (facing == "LEFT") {
        entitySprite.setScale(-1, 1);
    }
    else if (facing == "RIGHT")
    {
        entitySprite.setScale(1, 1);
    }
}

FloatRect PoissonGlobe::getHitBox()
{
	Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
	Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
	return FloatRect(boundsPos.x, boundsPos.y + boundsSize.y / 3.f, boundsSize.x, boundsSize.y / 3.f);
}
void PoissonGlobe::move()
{
}

void PoissonGlobe::pattern(EntityManager* manager)
{
    if (!manager->getAllPlayers().empty()) {
        shared_ptr<Player> player = std::static_pointer_cast<Player>(manager->getAllPlayers().front());
        update(player);
    }
}


void PoissonGlobe::grow()
{
    if (!isGrown) { 
        isGrown = true;
        growClock.restart(); 
    }
}

void PoissonGlobe::shrink()
{
    if (isGrown && growClock.getElapsedTime().asSeconds() > 5.0f) 
    {
        isGrown = false;
    }
}



bool PoissonGlobe::checkCollision(shared_ptr<Player> player) {
    return getHitBox().intersects(player->getHitBox());
}

void PoissonGlobe::update(shared_ptr<Player> player)
{
    shrink();
}
void PoissonGlobe::pushPlayer(shared_ptr<Player> player) {

    Vector2f direction = player->entitySprite.getPosition() - entitySprite.getPosition();


    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }


    float pushStrength = 55.0f;
    player->entitySprite.move(direction * pushStrength);
}

bool PoissonGlobe::getIsGrown() const { return isGrown; }