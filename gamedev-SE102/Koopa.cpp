#include "Koopa.h"
#include "ParaGoomba.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"
#include "QuestionBrick.h"
#include "VenusFireTrap.h"
#include "PiranhaPlant.h"
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPA_BBOX_WIDTH / 2;
	top = y - KOOPA_BBOX_HEIGHT / 2;
	right = left + KOOPA_BBOX_WIDTH;
	bottom = top + KOOPA_BBOX_HEIGHT;
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == KOOPA_STATE_WAITING) {
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);

		if (x - cx <= CGame::GetInstance()->GetBackBufferWidth() + KOOPA_BBOX_WIDTH)
		{
			WakeUp();
		}
		return;
	}
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - state_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if ((state == KOOPA_STATE_INSHELL) && (GetTickCount64() - state_start > KOOPA_SHELL_TIMEOUT))
	{
		SetState(KOOPA_STATE_REVIVING);
		return;
	}
	if ((state == KOOPA_STATE_REVIVING) && (GetTickCount64() - state_start > KOOPA_REVIVING_TIMEOUT))
	{
		SetState(KOOPA_STATE_WALKING);
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	switch (state)
	{
	case KOOPA_STATE_WAITING:
		return;
	case KOOPA_STATE_INSHELL:
		if (isFlipped) aniId = ID_ANI_KOOPA_INSHELL_FLIP;
		else aniId = ID_ANI_KOOPA_INSHELL;
		break;
	case KOOPA_STATE_WALKING:
		if (direction > 0) aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		else aniId = ID_ANI_KOOPA_WALKING_LEFT;
		break;
	case KOOPA_STATE_REVIVING:
		if (isFlipped) aniId = ID_ANI_KOOPA_REVIVING_FLIP;
		else aniId = ID_ANI_KOOPA_REVIVING;
		break;
	case KOOPA_STATE_SPINNING:
		if (isFlipped) aniId = ID_ANI_KOOPA_SPINNING_FLIP;
		else aniId = ID_ANI_KOOPA_SPINNING;
		break;
	case KOOPA_STATE_DIE:
		aniId = ID_ANI_KOOPA_DIE;
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

CKoopa::CKoopa(float x, float y)
{
	SetState(KOOPA_STATE_WAITING);
	state_start = -1;

}

void CKoopa::SetState(int _state)
{
	state = _state;
	state_start = GetTickCount64();
	switch (_state)
	{
	case KOOPA_STATE_WAITING:
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		ay = KOOPA_GRAVITY;
		vx = direction * KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_DIE:
		ay = KOOPA_GRAVITY;
		vy = KOOPA_DIE_SPEED_BY_KOOPA;
		break;
	case KOOPA_STATE_INSHELL:

	case KOOPA_STATE_REVIVING:
		vx = 0;
		ay = KOOPA_GRAVITY;
		ax = 0;
		break;
	case KOOPA_STATE_SPINNING:
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

void CKoopa::GetTailHit(int direction)
{

}

void CKoopa::GetKoopaHit(int _direction)
{
	if (_direction < 0) direction = -1;
	else direction = 1;
	vx = direction * KOOPA_WALKING_SPEED;
	SetState(KOOPA_STATE_DIE);
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::WakeUp()
{
	direction = 1;
	SetState(KOOPA_STATE_WALKING);
	isFlipped = false;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
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
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		ReverseDirection();
		CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(e->obj);
		if (brick) {
			if (brick->GetState() == QUESTION_BRICK_STATE_NORMAL && state == KOOPA_STATE_SPINNING) {
				brick->SpawnItem();
				brick->SetState(QUESTION_BRICK_STATE_HITTED);
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
		if (e->obj->GetState() == KOOPA_STATE_SPINNING) GetKoopaHit(-e->nx);
		((CKoopa*)e->obj)->GetKoopaHit(e->nx);
	}
	else {
		ReverseDirection();
		((CKoopa*)e->obj)->ReverseDirection();
	}
}

void CKoopa::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SPINNING) {
		((CVenusFireTrap*)e->obj)->HittedByKoopa();
	}
}

void CKoopa::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SPINNING) {
		((CPiranhaPlant*)e->obj)->HittedByKoopa();
	}
}

void CKoopa::ReverseDirection()
{
	vx = -vx;
	direction = -direction;
}
