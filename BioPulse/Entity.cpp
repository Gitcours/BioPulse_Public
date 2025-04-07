#include "Entity.h"

Entity::Entity(Vector2f _pos, Texture& _text, int _hp) : position(_pos), entityText(_text), health(_hp)
{ 
	entitySprite.setTexture(entityText); 
	entitySprite.setPosition(position);
	entitySprite.setTextureRect(IntRect(0, 0, entityText.getSize().y, entityText.getSize().y));
}

void Entity::draw(RenderWindow& window) { window.draw(entitySprite); }

int Entity::getHealth() const { return health; }
void Entity::setHealth(int _hp) { health = _hp; }