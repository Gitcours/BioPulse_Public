#include "Animation.h"

int Animation::continueAnimation(Sprite& sprite)
{
	texture = sprite.getTexture();
	if (sprite.getTextureRect().left >= texture->getSize().x - sprite.getTextureRect().width) {
		sprite.setTextureRect(IntRect(0, 0, sprite.getTextureRect().width, sprite.getTextureRect().height));
		return 1;
	}
	else 
	{
		IntRect rect = sprite.getTextureRect();
		rect.left += sprite.getTextureRect().width;
		sprite.setTextureRect(rect);
		return 0;
	}
}