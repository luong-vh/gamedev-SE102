#pragma once
#include "GameObject.h"
#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.04f
#define KOOPA_SPINNING_SPEED 0.15f
#define KOOPA_DIE_SPEED_BY_KOOPA -0.4f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 16

#define KOOPA_STATE_WAITING 0
#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_INSHELL 200
#define KOOPA_STATE_SPINNING 300
#define KOOPA_STATE_REVIVING 400
#define KOOPA_STATE_DIE 500

#define ID_ANI_KOOPA_WALKING_RIGHT 30000
#define ID_ANI_KOOPA_WALKING_LEFT 30010
#define ID_ANI_KOOPA_INSHELL 30100
#define ID_ANI_KOOPA_INSHELL_FLIP 30110
#define ID_ANI_KOOPA_SPINNING 30200
#define ID_ANI_KOOPA_SPINNING_FLIP 30210
#define ID_ANI_KOOPA_REVIVING 30300
#define ID_ANI_KOOPA_REVIVING_FLIP 30310
#define ID_ANI_KOOPA_DIE 30400

#define KOOPA_DIE_TIMEOUT 500
#define KOOPA_SHELL_TIMEOUT 10000
#define KOOPA_REVIVING_TIMEOUT 5000
#define KOOPA_TAIL_HIT_VY 0.5f
#define KOOPA_TAIL_HIT_VX 0.07f

class CKoopa : public CGameObject
{
protected:
   int direction;
   float ax;
   float ay;
 
   bool isFlipped;
   bool isOnPlatform;

   ULONGLONG state_start;

   virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
   virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
   virtual void Render();

   virtual int IsCollidable() { return 1; };
   virtual int IsBlocking() { return 0; }
   virtual void OnNoCollision(DWORD dt);
   virtual void WakeUp();
   virtual void OnCollisionWith(LPCOLLISIONEVENT e);
   virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
   virtual void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
   virtual void OnCollisionWithVenus(LPCOLLISIONEVENT e);
   virtual void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
   

public:
	bool isBeingHeld;
   CKoopa(float x, float y);
   virtual void ReverseDirection();
   virtual void SetState(int state);
   virtual void GetStomped();
   virtual void GetKicked(int);
   virtual void GetTailHit(int);
   virtual void GetKoopaHit(int);
   virtual void BeingHeld() { isBeingHeld = true; }
   virtual void Release(int nx);
};


