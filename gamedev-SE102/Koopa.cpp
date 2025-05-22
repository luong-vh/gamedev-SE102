#include "Koopa.h"
#include "ParaGoomba.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"
#include "QuestionBrick.h"
#include "VenusFireTrap.h"
#include "PiranhaPlant.h"
#include "GoldenBrick.h"
#include "ButtonBrick.h"
#include "KillZone.h"
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPA_BBOX_WIDTH / 2;
	top = y - KOOPA_BBOX_HEIGHT / 2 ;
	right = left + KOOPA_BBOX_WIDTH;
	bottom = top + KOOPA_BBOX_HEIGHT ;
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == KOOPA_STATE_WAITING) {
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);
		float w = CGame::GetInstance()->GetBackBufferWidth();

		if ((x < cx - KOOPA_BBOX_WIDTH && x > cx - 2 * KOOPA_BBOX_WIDTH) ||
			(x > cx + w + KOOPA_BBOX_WIDTH && x < cx + w + 2 * KOOPA_BBOX_WIDTH))
		{
			x = start_x;
			y = start_y;
			WakeUp();
			return;
		}
		
	}
	vy += ay * dt;
	vx += ax * dt;
	ULONGLONG deltaTime =  ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetDeltaTime(state_start);
	if ((state == KOOPA_STATE_DIE) && (deltaTime > KOOPA_DIE_TIMEOUT))
	{
		SetState(KOOPA_STATE_WAITING);
		return;
	}
	if ((state == KOOPA_STATE_INSHELL) && (deltaTime > KOOPA_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_REVIVING);
		return;
	}
	if ((state == KOOPA_STATE_REVIVING) && (deltaTime > KOOPA_REVIVING_TIMEOUT))
	{
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	if (!isBeingHeld) CCollision::GetInstance()->Process(this, dt, coObjects);
	if (state == KOOPA_STATE_INSHELL && isOnPlatform) vx = 0;
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	GetAniId(aniId);
	if (aniId != 0) CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CKoopa::RenderWhenMarioPaused()
{
	int aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	GetAniId(aniId);
	if (aniId != 0) CAnimations::GetInstance()->Get(aniId)->RenderCurrentFrame(x, y);
}

void CKoopa::GetAniId(int& aniId)
{
	aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	switch (state)
	{
	case KOOPA_STATE_WAITING:
		aniId = 0;
		return;
	case KOOPA_STATE_INSHELL:
		if (isFlipped) aniId = ID_ANI_KOOPA_INSHELL_FLIP;
		else aniId = ID_ANI_KOOPA_INSHELL;
		return;
	case KOOPA_STATE_WALKING:
		if (direction > 0) aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		else aniId = ID_ANI_KOOPA_WALKING_LEFT;
		return;
	case KOOPA_STATE_REVIVING:
		if (isFlipped) aniId = ID_ANI_KOOPA_REVIVING_FLIP;
		else aniId = ID_ANI_KOOPA_REVIVING;
		return;
	case KOOPA_STATE_SPINNING:
		if (isFlipped) aniId = ID_ANI_KOOPA_SPINNING_FLIP;
		else aniId = ID_ANI_KOOPA_SPINNING;
		return;
	case KOOPA_STATE_DIE:
		aniId = ID_ANI_KOOPA_DIE;
		return;
	default:
		break;
	}
}

CKoopa::CKoopa(float x, float y)
{
	state_start = -1;
	isBeingHeld = false;
	isOnPlatform = false;
	start_x = x;
	start_y = y;
	SetState(KOOPA_STATE_WAITING);
}

void CKoopa::SetState(int _state)
{
	state = _state;
	state_start = GetTickCount64();
	switch (_state)
	{
	case KOOPA_STATE_WAITING:
		isBeingHeld = false;
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		x = start_x;
		y = start_y + 500;
		break;
	case KOOPA_STATE_WALKING:

		isFlipped = false;
		isBeingHeld = false;
		ay = KOOPA_GRAVITY;
		vx = direction * KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_DIE:
		ay = KOOPA_GRAVITY;
		vy = KOOPA_DIE_SPEED_BY_KOOPA;
		isBeingHeld = false;
		break;
	case KOOPA_STATE_INSHELL:

	case KOOPA_STATE_REVIVING:
		vx = 0;
		ay = KOOPA_GRAVITY;
		ax = 0;
		break;
	case KOOPA_STATE_SPINNING:
		isBeingHeld = false;
		ay = KOOPA_GRAVITY;
		vx = direction * KOOPA_SPINNING_SPEED;
		break;
	default:

		break;
	}

}
void CKoopa::GetKicked(int _direction) 
{
	if (_direction < 0) direction = -1;
	else direction = 1;
	SetState(KOOPA_STATE_SPINNING);
}

void CKoopa::GetStomped()
{
	switch (state) {
	case KOOPA_STATE_WALKING:
	case KOOPA_STATE_SPINNING:
	case KOOPA_STATE_REVIVING:
		SetState(KOOPA_STATE_INSHELL);
		break;
	case KOOPA_STATE_INSHELL:
		float mx, my;
		((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetPosition(mx, my);
		direction = mx < x ? 1 : -1;
		SetState(KOOPA_STATE_SPINNING);
	}
}

void CKoopa::GetTailHit(int _direction)
{
	isFlipped = true;
	if (_direction < 0) direction = -1;
	else direction = 1;

	SetState(KOOPA_STATE_INSHELL);
	vx = direction * KOOPA_TAIL_HIT_VX;
	vy = -KOOPA_TAIL_HIT_VY;
}

void CKoopa::GetKoopaHit(int _direction)
{
	if (_direction < 0) direction = -1;
	else direction = 1;
	vx = direction * KOOPA_WALKING_SPEED;
	SetState(KOOPA_STATE_DIE);
}

void CKoopa::Release(int nx)
{
	y -= 5;
	isBeingHeld = false;	
	if (nx < 0) direction = -1;
	else direction = 1;
	SetState(KOOPA_STATE_SPINNING);
	
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CKoopa::WakeUp()
{
	direction = -1;
	SetState(KOOPA_STATE_WALKING);
	isFlipped = false;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	if (dynamic_cast<CGoomba*>(e->obj)) {
		if (e->obj->GetState() == GOOMBA_STATE_DIE) return;
		OnCollisionWithGoomba(e);
		return;
	}
	if (dynamic_cast<CKoopa*>(e->obj)) {
		if (e->obj->GetState() == KOOPA_STATE_DIE) return;
		OnCollisionWithKoopa(e);
		return;
	}
	if (dynamic_cast<CVenusFireTrap*>(e->obj)) {
		OnCollisionWithVenus(e);
		return;
	}
	if (dynamic_cast<CPiranhaPlant*>(e->obj)) {
		OnCollisionWithPiranha(e);
		return;
	}
	else if (dynamic_cast<CKillZone*>(e->obj)) {
		SetState(KOOPA_STATE_WAITING);
		return;
	}
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoldenBrick*>(e->obj)) {
			CGoldenBrick* goldenBrick = dynamic_cast<CGoldenBrick*>(e->obj);
			if (e->nx!=0 && goldenBrick->GetState() == GOLDEN_BRICK_STATE_NORMAL && state == KOOPA_STATE_SPINNING) {
				goldenBrick->Break();
				ReverseDirection();
			}
			else if (e->nx != 0 && goldenBrick->GetState() == GOLDEN_BRICK_STATE_NORMAL && state == KOOPA_STATE_WALKING) {
				ReverseDirection();
			}
		
		return;
	}
	else if (dynamic_cast<CButtonBrick*>(e->obj)) {
		CButtonBrick* buttonBrick = dynamic_cast<CButtonBrick*>(e->obj);
		if (e->ny != 0 && buttonBrick->GetState() == BUTTON_BRICK_STATE_NORMAL) {
			buttonBrick->SetState(BUTTON_BRICK_STATE_MOVE_UP);
		}
		else if (e->ny !=0) ReverseDirection();
		return;
	}

	else if (e->nx != 0)
	{
		ReverseDirection();
		CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(e->obj);
		if (brick) {
			if (brick->GetState() == QUESTION_BRICK_STATE_NORMAL && state == KOOPA_STATE_SPINNING) {
				brick->SpawnItem();
				brick->SetState(QUESTION_BRICK_STATE_HIT);
			}
		}
	}
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SPINNING) {
		if (e->obj->GetState() == GOOMBA_STATE_WALKING || e->obj->GetState() == GOOMBA_STATE_PARA) 
			((CGoomba*)e->obj)->GetKoopaHit(-e->nx);
		return;
	}
	else if (e->obj->GetState() == GOOMBA_STATE_PARA) return;
	ReverseDirection();
	((CGoomba*)e->obj)->ReverseDirection();
	
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SPINNING) {
		
		((CKoopa*)e->obj)->GetKoopaHit(e->nx);
	}
	if (e->obj->GetState() == KOOPA_STATE_SPINNING) GetKoopaHit(-e->nx);
	else if (((CKoopa*)e->obj)->isBeingHeld) {
		GetKoopaHit(nx);
		((CKoopa*)e->obj)->GetKoopaHit(-nx);
	}
	else {
		ReverseDirection();
		((CKoopa*)e->obj)->ReverseDirection();
	}
}

void CKoopa::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SPINNING) {
		((CVenusFireTrap*)e->obj)->HitByKoopa();
	}
}

void CKoopa::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SPINNING) {
		((CPiranhaPlant*)e->obj)->HitByKoopa();
	}
}

void CKoopa::ReverseDirection()
{
	vx = -vx;
	direction = -direction;
}
