#include "PiranhaPlant.h"
#include "Piranha_Pipe.h"
#include "Mario.h"
#include "PlayScene.h"
void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	ULONGLONG deltaTime = GetTickCount64() - state_start;
	switch (state)
	{
	case PIRANHA_DIE_STATE:
		if (deltaTime > PIRANHA_DIE_TIMEOUT)
		{
			isDeleted = true;
			return;
		}
		break;
	case PIRANHA_RISE_STATE:
		if (y <= minY)
		{
			y = minY;
			SetState(PIRANHA_ATTACK_STATE);
			return;
		}
		break;
	case PIRANHA_DIVE_STATE:
		if (y >= maxY)
		{
			y = maxY;
			SetState(PIRANHA_HIDE_STATE);
			return;
		}
		break;
	case PIRANHA_HIDE_STATE:
		float mx, my;
		((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetPosition(mx, my);
		if (isRisable && abs(mx - x) <= CGame::GetInstance()->GetBackBufferWidth() / 2 && deltaTime > PIRANHA_HIDE_TIMEOUT)
		{
			SetState(PIRANHA_RISE_STATE);
			return;
		}
		break;
	case PIRANHA_ATTACK_STATE:
		if (deltaTime > PIRANHA_ATTACK_TIMEOUT)
		{
			SetState(PIRANHA_DIVE_STATE);
			return;
		}
		break;
	}
}

void CPiranhaPlant::Render()
{
	if (state == PIRANHA_HIDE_STATE) return;
	CAnimations::GetInstance()->Get(PIRANHA_ANIMATION_ID)->Render(x, y);
}

void CPiranhaPlant::SetState(int _state)
{
	this->state = _state;
	state_start = GetTickCount64();
	switch (this->state)
	{
	case PIRANHA_DIE_STATE:
		pipe->piranhaPlant = NULL;
		vx = 0;
		vy = 0;
		break;
	case PIRANHA_RISE_STATE:
		vx = 0;
		vy = -PIRANHA_SPEED;
		break;
	case PIRANHA_DIVE_STATE:
		vx = 0;
		vy = PIRANHA_SPEED;
		break;
	case PIRANHA_HIDE_STATE:
		vx = 0;
		vy = 0;
		break;
	case PIRANHA_ATTACK_STATE:
		vx = 0;
		vy = 0;
		break;
	}
}

void CPiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_CELL_WIDTH / 2;
	t = y - PIRANHA_CELL_HEIGHT / 2 * this->height + 1;
	r = l + PIRANHA_CELL_WIDTH;
	b = t + PIRANHA_CELL_HEIGHT * this->height;
}

