#pragma once
#include "GameObject.h"
#include "FireBullet.h"
#define RED_VENUSFIRETRAP_ID 90000
#define GREEN_VENUSFIRETRAP_ID 100000

#define VENUS_RISE_STATE 0
#define VENUS_DIVE_STATE 1000
#define VENUS_SHOOT_STATE 2000
#define VENUS_HIDE_STATE 3000
#define VENUS_DIE_STATE 4000

#define VENUS_HEAD_UP 0
#define VENUS_HEAD_DOWN 100

#define VENUS_HEAD_LEFT 0
#define VENUS_HEAD_RIGHT 10

#define VENUS_ATTACK_RANGE 90.0f
#define VENUS_SPEED 0.03f

#define VENUS_CELL_WIDTH 16
#define VENUS_CELL_HEIGHT 8

#define VENUS_DIE_TIMEOUT 500
#define VENUS_PRE_SHOOT_TIMEOUT 500
#define VENUS_SHOOT_TIMEOUT 1000
#define VENUS_HIDE_TIMEOUT 1000

class CVenus_Pipe;
typedef CVenus_Pipe* LPVenusPipe;
class CVenusFireTrap :public CGameObject
{
private:
	LPFIREBULLET fireBullet;
	ULONGLONG state_start;
	int state;
	int objectId;
	int height;
	float minY, maxY;
	bool isShooted;
public:

	LPVenusPipe pipe;
	bool isRisable;
	CVenusFireTrap(float x, float y, 
	int height,
		LPVenusPipe _pipe,int object_id) : CGameObject(x, y)
	{
		this->fireBullet = new CFireBullet(x, y - (VENUS_CELL_HEIGHT * height) / 2.0f + VENUS_CELL_HEIGHT);
		isRisable = true;
		state_start = -1;
		this->height = height;
		this->pipe = _pipe;
		this->minY = y;
		this->maxY = y + height * VENUS_CELL_HEIGHT;
		this->objectId = object_id;
		SetState(VENUS_RISE_STATE);
		vy = -VENUS_SPEED;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; };
};
typedef CVenusFireTrap* LPVENUSFIRETRAP;
