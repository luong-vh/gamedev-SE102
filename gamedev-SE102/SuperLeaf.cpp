#include "SuperLeaf.h"
#include "debug.h"
#include "PlayScene.h"
#include "Mario.h"

#define PI 3.141592653589793
void CSuperLeaf::Render()
{
	if (state == SUPER_LEAF_STATE_WAITING)
		return;
	CAnimations* animations = CAnimations::GetInstance();
	if (state == SUPER_LEAF_STATE_FALLING_RIGHT)
		animations->Get(ID_ANI_SUPER_LEAF_LEFT)->Render(x, y);
	else
		animations->Get(ID_ANI_SUPER_LEAF_RIGHT)->Render(x, y);
}

void CSuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == SUPER_LEAF_STATE_WAITING)
		return;
	
	float dy = 0;
	switch (state)
	{
	default:
		break;
	case SUPER_LEAF_STATE_RISE:
		y += vy * dt;
		if (y <= minY)
		{
			y = minY;
			SetState(SUPER_LEAF_STATE_FALLING_RIGHT);
		}
		break;
	case SUPER_LEAF_STATE_FALLING_RIGHT:
		x += vx * dt;
		if (x >= maxX)
		{
			x = maxX;
		}
		 dy = (sin((x - minX) / 8 - PI / 2) + 1)*20 / 3.0f ;
		
		y = minY + dy;
	
		if (x >= maxX) 
		{
			SetState(SUPER_LEAF_STATE_FALLING_LEFT);
			
		}
		break;
	case SUPER_LEAF_STATE_FALLING_LEFT:
		x += vx * dt;
		if (x <= minX)
		{
			x = minX;
		}
		dy = ((sin((x - minX) / 8 + 3 * PI / 2 - 4)) + 1) * 20/ 3.0f ;
		
		y = minY + dy;
		if (x <= minX)
		{
			SetState(SUPER_LEAF_STATE_FALLING_RIGHT);
			
		}
	}
	
	
}

void CSuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_LEAF_BBOX_WIDTH / 2;
	t = y - SUPER_LEAF_BBOX_HEIGHT / 2;
	r = l + SUPER_LEAF_BBOX_WIDTH;
	b = t + SUPER_LEAF_BBOX_HEIGHT;
}

void CSuperLeaf::SetState(int _state)
{
	this->state = _state;
	switch (_state)
	{
	case SUPER_LEAF_STATE_WAITING:
		vy = 0;
		vx = 0;
		break;
	case SUPER_LEAF_STATE_RISE:
		vy = -SUPER_LEAF_SPEED;
		vx = 0;
		break;
	case SUPER_LEAF_STATE_FALLING_RIGHT:
		vy = 0;
		vx = SUPER_LEAF_SPEED;
		minY = y;
		break;
	case SUPER_LEAF_STATE_FALLING_LEFT:
		vy = 0;
		vx = -SUPER_LEAF_SPEED;
		minY = y;
		break;
	}
}

void CSuperLeaf::Delete()
{
	this->isDeleted = true;
	SetState(SUPER_LEAF_STATE_WAITING);
}
