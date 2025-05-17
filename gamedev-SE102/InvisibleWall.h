#pragma once
#include "GameObject.h"
#include "Game.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Collision.h"
class CInvisibleWall :
    public CGameObject
{
public:
	CInvisibleWall(float x, float y) : CGameObject(x, y)
	{
		this->x = x;
		this->y = y;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		

	}

	void Render()
	{
		RenderBoundingBox();
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - 4;
		t = y - 1000;
		r = l + 8;
		b = t + 2000;
	}
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};

