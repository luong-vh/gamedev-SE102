#include "SuperMushroom.h"
#include "debug.h"
#include "PlayScene.h"
#include "Mario.h"
void CSuperMushroom::Render()
{
	if (state == SUPER_MUSHROOM_STATE_WAITING)
		return;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SUPER_MUSHROOM)->Render(x, y);
}

void CSuperMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == SUPER_MUSHROOM_STATE_WAITING)
		return;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	LPCOLLISIONEVENT e = CCollision::GetInstance()->SweptAABB(this, dt, mario);
	if (e->WasCollided()) {
		Delete();
		mario->OnCollisionWithSuperMushroom(e);
	}
	
	
	if (state == SUPER_MUSHROOM_STATE_RISE)
	{
		y += vy * dt;
		if (y <= minY)
		{

			y = minY;
			SetState(SUPER_MUSHROOM_STATE_MOVING);
		}
	}
	else if (state == SUPER_MUSHROOM_STATE_MOVING)
	{
		vy += SUPER_MUSHROOM_GRAVITY * dt;
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	
}

void CSuperMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_MUSHROOM_BBOX_WIDTH / 2;
	t = y - SUPER_MUSHROOM_BBOX_HEIGHT / 2;
	r = l + SUPER_MUSHROOM_BBOX_WIDTH;
	b = t + SUPER_MUSHROOM_BBOX_HEIGHT;
}

void CSuperMushroom::SetState(int _state)
{
	state = _state;
	switch (_state)
	{
	case SUPER_MUSHROOM_STATE_WAITING:
		vy = 0;
		vx = 0;
		break;
	case SUPER_MUSHROOM_STATE_RISE:
		vy = -SUPER_MUSHROOM_SPEED_RISE;
		vx = 0;
		break;
	case SUPER_MUSHROOM_STATE_MOVING:
		if (direction > 0)
			vx = SUPER_MUSHROOM_SPEED_X;
		else
			vx = -SUPER_MUSHROOM_SPEED_X;
		break;
	}
}

void CSuperMushroom::Delete()
{
	isDeleted = true;
	SetState(SUPER_MUSHROOM_STATE_WAITING);
}
