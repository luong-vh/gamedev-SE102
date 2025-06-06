#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "Koopa.h"
#include "Tail.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601




#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 1000
#define ID_ANI_MARIO_IDLE_LEFT 1010
#define ID_ANI_MARIO_WARPING 1020
#define ID_ANI_MARIO_WALKING_RIGHT 1100
#define ID_ANI_MARIO_WALKING_LEFT 1110

#define ID_ANI_MARIO_RUNNING_RIGHT 1200
#define ID_ANI_MARIO_RUNNING_LEFT 1210

#define ID_ANI_MARIO_RUNNING_FULL_RIGHT 1300
#define ID_ANI_MARIO_RUNNING_FULL_LEFT 1310

#define ID_ANI_MARIO_JUMP_RIGHT 1400
#define ID_ANI_MARIO_JUMP_LEFT 1410

#define ID_ANI_MARIO_FALL_RIGHT 1500
#define ID_ANI_MARIO_FALL_LEFT 1510

#define ID_ANI_MARIO_JUMP_FULL_RIGHT 1600
#define ID_ANI_MARIO_JUMP_FULL_LEFT 1610

#define ID_ANI_MARIO_SIT_RIGHT 1700
#define ID_ANI_MARIO_SIT_LEFT 1710

#define ID_ANI_MARIO_BRACE_RIGHT 1800
#define ID_ANI_MARIO_BRACE_LEFT 1810

#define ID_ANI_MARIO_IDLE_HOLD_RIGHT 1900
#define ID_ANI_MARIO_IDLE_HOLD_LEFT 1910
#define ID_ANI_MARIO_JUMP_HOLD_RIGHT 1902
#define ID_ANI_MARIO_JUMP_HOLD_LEFT 1912
#define ID_ANI_MARIO_RUNNING_HOLD_RIGHT 1901
#define ID_ANI_MARIO_RUNNING_HOLD_LEFT 1911
#define ID_ANI_MARIO_KICK_RIGHT 1903
#define ID_ANI_MARIO_KICK_LEFT 1913

#define ID_ANI_MARIO_DIE 3000

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 2
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 10
#define ID_ANI_MARIO_SMALL_WARPING 20
#define ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT 900
#define ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT 910

#define ID_ANI_MARIO_SMALL_JUMP_HOLD_RIGHT 901
#define ID_ANI_MARIO_SMALL_JUMP_HOLD_LEFT 911

#define ID_ANI_MARIO_SMALL_RUNNING_HOLD_RIGHT 902
#define ID_ANI_MARIO_SMALL_RUNNING_HOLD_LEFT 912

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 903
#define ID_ANI_MARIO_SMALL_KICK_LEFT 913

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 100
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 110

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 200
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 210

#define ID_ANI_MARIO_SMALL_RUNNING_FULL_RIGHT 300
#define ID_ANI_MARIO_SMALL_RUNNING_FULL_LEFT 310

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 800
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 810

#define ID_ANI_MARIO_SMALL_JUMP_RIGHT 400
#define ID_ANI_MARIO_SMALL_JUMP_LEFT 410

#define ID_ANI_MARIO_SMALL_JUMP_FULL_RIGHT 600
#define ID_ANI_MARIO_SMALL_JUMP_FULL_LEFT 610

// RACOON MARIO
#define ID_ANI_MARIO_RACOON_IDLE_RIGHT 2000
#define ID_ANI_MARIO_RACOON_IDLE_LEFT 2010
#define ID_ANI_MARIO_RACOON_WARPING 2020

#define ID_ANI_MARIO_RACOON_WALKING_RIGHT 2100
#define ID_ANI_MARIO_RACOON_WALKING_LEFT 2110

#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT 2200
#define ID_ANI_MARIO_RACOON_RUNNING_LEFT 2210

#define ID_ANI_MARIO_RACOON_RUNNING_FULL_RIGHT 2300
#define ID_ANI_MARIO_RACOON_RUNNING_FULL_LEFT 2310

#define ID_ANI_MARIO_RACOON_JUMP_RIGHT 2400
#define ID_ANI_MARIO_RACOON_JUMP_LEFT 2410

#define ID_ANI_MARIO_RACOON_FALL_RIGHT 2500
#define ID_ANI_MARIO_RACOON_FALL_LEFT 2510

#define ID_ANI_MARIO_RACOON_JUMP_FULL_RIGHT 2600
#define ID_ANI_MARIO_RACOON_JUMP_FULL_LEFT 2610

#define ID_ANI_MARIO_RACOON_SIT_RIGHT 2700
#define ID_ANI_MARIO_RACOON_SIT_LEFT 2710

#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 2800
#define ID_ANI_MARIO_RACOON_BRACE_LEFT 2810

#define ID_ANI_MARIO_RACOON_SLOW_FALL_RIGHT 2940
#define ID_ANI_MARIO_RACOON_SLOW_FALL_LEFT 2942

#define ID_ANI_MARIO_RACOON_FLY_RIGHT 2950
#define ID_ANI_MATIO_RACOON_FLY_LEFT 2952
// TRANSFORM
#define ID_ANI_MARIO_TRANSFORM_SMALL_TO_BIG_RIGHT 4000
#define ID_ANI_MARIO_TRANSFORM_SMALL_TO_BIG_LEFT 4001
#define ID_ANI_MARIO_TRANSFORM_BIG_TO_SMALL_RIGHT 4002
#define ID_ANI_MARIO_TRANSFORM_BIG_TO_SMALL_LEFT 4003
#define ID_ANI_MARIO_TRANSFORM_SMOKE 4004

#define ID_ANI_MARIO_RACOON_IDLE_HOLD_RIGHT 2900
#define ID_ANI_MARIO_RACOON_IDLE_HOLD_LEFT 2910
#define ID_ANI_MARIO_RACOON_JUMP_HOLD_RIGHT 2902
#define ID_ANI_MARIO_RACOON_JUMP_HOLD_LEFT 2912
#define ID_ANI_MARIO_RACOON_RUNNING_HOLD_RIGHT 2901
#define ID_ANI_MARIO_RACOON_RUNNING_HOLD_LEFT 2911
#define ID_ANI_MARIO_RACOON_KICK_RIGHT 2903
#define ID_ANI_MARIO_RACOON_KICK_LEFT 2913
#define ID_ANI_MARIO_RACOON_TAIL_ATTACK_RIGHT 2930
#define ID_ANI_MARIO_RACOON_TAIL_ATTACK_LEFT 2931

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_FALLING_SPEED 0.05f
#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICK_TIMEOUT 200
#define MARIO_DIE_TIMEOUT 500
#define MARIO_SLOW_FALL_TIMEOUT 210
#define MARIO_CHARGE_POWER_UP_TIME 1200
#define MARIO_DRAIN_POWER_UP_TIME 300
#define MARIO_POWER_FULL_TIME 5000
#define MARIO_FLICKER_TIMEOUT 20
#define SMALL_OFFSET_X 10
#define SMALL_OFFSET_Y -2
#define BIG_OFFSET_X 12
#define BIG_OFFSET_Y -1

#define TAIL_OFFSET_X 10
#define TAIL_OFFSET_Y 4

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float slowFallTime;

	float drainTime;
	float chargeTime;
	float powerFullTime;
	float warpTime;
	int level; 
	int untouchable; 
	int chargeAble;
	bool isKicking;
	bool isAttacking;
	bool isRenderable;
	bool isFlyable;
	bool isGetCard;
	int idAniTransform;
	CKoopa* koopa;
	ULONGLONG untouchable_start;
	ULONGLONG kick_start;
	ULONGLONG attack_start;
	ULONGLONG die_start;
	ULONGLONG flicker_start;
	BOOLEAN isOnPlatform;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void HandleTailAttack(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HandlePowerUp(DWORD dt);
	void HandleKoopaHold();
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();
	CTail* tail;

public:
	float flyTime;
	bool ableToHold;
	bool ableToAttack;
	bool isAbleToRise;
	bool isAbleToDive;
	float vwarp;
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isKicking = false;
		isAttacking = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		ableToHold = false;
		ableToAttack = false;
		koopa = NULL;
		level = MARIO_LEVEL_SMALL;
		tail = NULL;
		untouchable = 0;
		untouchable_start = -1;
		kick_start = -1;
		attack_start = -1;
		isOnPlatform = false;
		isRenderable = true;
		slowFallTime = -1;
		drainTime = 0;
		chargeTime = 0;
		powerFullTime = 0;
		chargeAble = 0;
		flyTime = 0;
		isFlyable = true;
		isAbleToRise = false;
		isAbleToDive = false;
		isGetCard = false;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void OnGetDamage();
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; }
	void StartUntouchable() 
	{ 
		untouchable = 1; 
		untouchable_start = GetTickCount64(); 
		flicker_start = untouchable_start;
		isRenderable = true;
	}
	void HoldKoopa(CKoopa* k) { koopa = k; }
	void ReleaseKoopa() 
	{ 
		koopa = NULL; 
		OnGetDamage();
	}
	void GetKoopaOffset(float& offsetX, float& offsetY);
	
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void RenderWhenMarioPaused() {
		CAnimations::GetInstance()->Get(idAniTransform)->Render(x, y);
	}
	void SlowFall() {
		
		if (level == MARIO_LEVEL_RACOON) {
			if (powerFullTime > 0) {
				state = MARIO_STATE_JUMP;
				flyTime = MARIO_SLOW_FALL_TIMEOUT;
				chargeAble = 0;
				return;
			}
			if (isOnPlatform) SetState(MARIO_STATE_JUMP);
			else slowFallTime = MARIO_SLOW_FALL_TIMEOUT;
		}
		else SetState(MARIO_STATE_JUMP);
	}
	void Warp(float v, int time) {
		warpTime = time;
		vwarp = v;
	}
	void GetCard() {
		isGetCard = true;
	}
};