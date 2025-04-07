#include "Projectiles.h"

Projectiles::Projectiles(Vector2f _pos, Texture& _text, std::string _direction) : bulletmovdeltaTime(1), direction(_direction), Entity(Vector2f(_pos.x + 22, _pos.y + 15), _text, 0) {
    if (direction == "LEFT")
	{
        entitySprite.setScale(-1,1);
        entitySprite.setPosition(entitySprite.getPosition().x - 44, entitySprite.getPosition().y - entitySprite.getGlobalBounds().height / 2.f + 8.f);
	}
    entitySprite.setColor(sf::Color::Transparent);
    bulletStartDelataTime = bulletdeltaTime / 5;
    entityType = "Projectiles";
}

Projectiles::~Projectiles() {
}

void Projectiles::update() {
    if (bulletStartClock.getElapsedTime() >= sf::seconds(bulletStartDelataTime))
    {
        entitySprite.setColor(sf::Color::White);
        if (moveclock.getElapsedTime() >= sf::milliseconds(bulletmovdeltaTime))
        {
            moveclock.restart();
            if (direction == "LEFT")
            {
                entitySprite.move(-bulletspeed, 0);
            }
            else
            {
                entitySprite.move(bulletspeed, 0);
            }
        }
    }
}

FloatRect Projectiles::getHitBox()
{
    Vector2f boundsPos = entitySprite.getGlobalBounds().getPosition();
    Vector2f boundsSize = entitySprite.getGlobalBounds().getSize();
    return FloatRect(boundsPos.x + boundsSize.x / 4.f, boundsPos.y + boundsSize.y / 2.2f, boundsSize.x / 1.2f, boundsSize.y / 6.f);
}