#pragma once
#include "Goomba.h"
#define GOOMBA_STATE_PARA 500

#define ID_ANI_PARA_GOOMBA_WALKING 21000
#define ID_ANI_PARA_GOOMBA_DIE 21100
#define ID_ANI_PARA_GOOMBA_DIE_BY_TAIL 21101
#define ID_ANI_PARA_GOOMBA_JUMP 21021
#define ID_ANI_PARA_GOOMBA_FLY 21020
#define ID_ANI_PARA_GOOMBA_WALKING_WING 21010

#define PARA_GOOMBA_JUMP_SPEED 0.2f
#define PARA_GOOMBA_WALK_TIMEOUT 1000
#define PARA_GOOMBA_TOTALSTEPS 5
#define PARA_GOOMBA_MAX_CHASE 7
class CParaGoomba :
    public CGoomba
{
private:
	float startX, startY;
	bool isOnPlatform;
	int currentStep;
	int direction;
	float timeStep;
	bool isChase;
	int chaseCount;
public:
	CParaGoomba(float x, float y) : CGoomba(x, y)
	{
		startX = x;
		startY = y;
		this->ax = 0;
		this->ay = GOOMBA_GRAVITY;
		die_start = -1;
		SetState(GOOMBA_STATE_WAITING);
		
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void WakeUp();
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
	void StartFisrtStep();
	void GetStomped();
};

