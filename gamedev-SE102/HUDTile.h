#pragma once
#include "Sprite.h"
class CHUDTile
{
	LPSPRITE sprite;
	float x, y;
public:
	CHUDTile(LPSPRITE sprite, float x, float y) : sprite(sprite), x(x), y(y) {}
	void Draw() { sprite->DrawOnScreen(x, y); }
	void SetSprite(LPSPRITE sprite) { this->sprite = sprite; }
};

