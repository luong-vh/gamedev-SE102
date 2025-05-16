#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.04f
#define GOOMBA_DIE_SPEED_BY_KOOPA -0.4f
#define GOOMBA_DIE_SPEED_BY_TAIL -0.5f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WAITING 0
#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_DIE_BY_TAIL 300
#define GOOMBA_STATE_DIE_BY_KOOPA 400

#define ID_ANI_GOOMBA_WALKING 20000
#define ID_ANI_GOOMBA_DIE 20100
#define ID_ANI_GOOMBA_DIE_BY_TAIL 20101


class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void WakeUp();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	
	
public: 	
	virtual void ReverseDirection() { vx = -vx; }
	CGoomba(float x, float y);
	virtual void SetState(int state);
	virtual void GetStomped();
	virtual void GetKoopaHit(int);
	virtual void GetTailHit(int);
};