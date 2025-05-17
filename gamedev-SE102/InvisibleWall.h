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
		
		CGameObject* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		vector<LPGAMEOBJECT> temp ;
		temp.push_back(mario); // Explicit cast to LPGAMEOBJECT*
		CCollision::GetInstance()->Process(this, dt, &temp);

	}
	void Render()
	{
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - 4;
		t = y - 1000;
		r = l + 8;
		b = t + 2000;
	}
	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }
};

