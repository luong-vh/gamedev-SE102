#include "VenusFireTrap.h"
#include "Venus_Pipe.h"
#include "Mario.h"
#include "PlayScene.h"
void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	y += vy * dt;
	ULONGLONG deltaTime = GetTickCount64() - state_start; 
	switch (state)
	{
	case VENUS_DIE_STATE:
		if (deltaTime > VENUS_DIE_TIMEOUT)
		{
			isDeleted = true;
			return;
		}
		break;
	case VENUS_SHOOT_STATE:
		
		
		if (deltaTime > VENUS_PRE_SHOOT_TIMEOUT && !isShooted)
		{
			
			fireBullet->Shoot();
			isShooted = true;
		}
		if (deltaTime > VENUS_SHOOT_STATE )
		{
			SetState(VENUS_DIVE_STATE);
			return;
		}
		break;
	case VENUS_RISE_STATE:
		
		if (y <= minY)
		{
			y = minY;
			SetState(VENUS_SHOOT_STATE);
			return;
		}
		break;
	case VENUS_DIVE_STATE:
		if (y >= maxY)
		{
			y = maxY;
			SetState(VENUS_HIDE_STATE);
			return;
		}
		break;
	case VENUS_HIDE_STATE:
		float mx, my;
		((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer())->GetPosition(mx, my);
		if (isRisable && abs(mx-x) <= CGame::GetInstance()->GetBackBufferWidth() /2 && deltaTime > VENUS_HIDE_TIMEOUT)
		{
			SetState(VENUS_RISE_STATE);
			return;
		}
	}
	this->fireBullet->Update(dt, coObjects);
}

void CVenusFireTrap::Render()
{
	if (state == VENUS_HIDE_STATE) return;
	
	int aniId = state + objectId;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mx, my;
	mario->GetPosition(mx, my);

	if (my > this->y - VENUS_CELL_HEIGHT) {
		aniId += VENUS_HEAD_DOWN;
	}
	else {
		aniId += VENUS_HEAD_UP;
	}
	if (mx > this->x) {
		aniId += VENUS_HEAD_RIGHT;
	}
	else {
		aniId += VENUS_HEAD_LEFT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	this->fireBullet->Render();
}

void CVenusFireTrap::SetState(int state)
{
	this->state = state;
	state_start = GetTickCount64();
	switch (state)
	{
	case VENUS_DIE_STATE:
		this->pipe->venusFireTrap = NULL;
		vx = 0;
		vy = 0;
		break;
	case VENUS_RISE_STATE:
		vx = 0;
		vy = -VENUS_SPEED;
		break;
	case VENUS_DIVE_STATE:
		vx = 0;
		vy = VENUS_SPEED;
		break;
	case VENUS_SHOOT_STATE:
		isShooted = false;
		vx = 0;
		vy = 0;
		break;
	case VENUS_HIDE_STATE:
		vx = 0;
		vy = 0;
		break;
	}
}

void CVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VENUS_CELL_WIDTH /2;
	t = y - VENUS_CELL_HEIGHT / 2 * this ->height +1;
	r = l + VENUS_CELL_WIDTH;
	b = t + VENUS_CELL_HEIGHT * this->height;
}
