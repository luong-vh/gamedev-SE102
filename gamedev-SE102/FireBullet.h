#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"
#define FIRE_BULLET_SPEED_X 0.1f
#define FIRE_BULLET_SPEED_Y 0.1f
#define FIRE_BULLET_WIDTH 8
#define FIRE_BULLET_HEIGHT 8

#define FIRE_BULLET_ANIMATION_ID_LEFT 110000
#define FIRE_BULLET_ANIMATION_ID_RIGHT 110001

#define FIRE_BULLET_STATE_WAITING 0
#define FIRE_BULLET_STATE_LEFT_SHOOTING 1
#define FIRE_BULLET_STATE_RIGHT_SHOOTING 2
class CFireBullet :
    public CGameObject
{
private:
	float start_x, start_y;
	CMario* mario;
public:
	CFireBullet(float x, float y) : CGameObject(x, y)
	{
		CPlayScene* currentScene = (CPlayScene*)(CGame::GetInstance()->GetCurrentScene());
		//currentScene->AddObject(this);
		mario = (CMario*)currentScene->GetPlayer();
		this->start_x = x;
		this->start_y = y;
		this->vx = FIRE_BULLET_SPEED_X ;
		this->vy = FIRE_BULLET_SPEED_Y ;
		SetState(FIRE_BULLET_STATE_WAITING);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetState(int state);
	int IsBlocking() { return 0; }
	void Shoot();
};

typedef CFireBullet* LPFIREBULLET;