#include "Coin.h"
#include "debug.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameData.h"
#include "PlayHUD.h"
void CCoin::Render()
{
	if (state == COIN_STATE_WAITING)
		return;
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == COIN_STATE_NORMAL)
		aniId = ID_ANI_COIN_NORMAL;
	else
		aniId = ID_ANI_COIN_BRICK;
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == COIN_STATE_WAITING || state == COIN_STATE_NORMAL)
		return;
	y += vy * dt;
	if (state == COIN_STATE_MOVING_UP)
	{
		if (y <= minY)
		{
			y = minY;
			SetState(COIN_STATE_MOVING_DOWN);
		}
	}
	else if (state == COIN_STATE_MOVING_DOWN)
	{
		if (y >= maxY)
		{
			Delete();
			CGameData::AddCoin(1);
			CGameData::AddScore(100);
			CPlayHUD::GetInstance()->SetCoin(CGameData::coin);
			CPlayHUD::GetInstance()->SetScore(CGameData::score);
			SetState(COIN_STATE_WAITING);
		}
	}
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::SetState(int _state)
{
	CGameObject::SetState(_state);
	switch (_state)
	{
	case COIN_STATE_NORMAL:
		vy = 0;
		break;
	case COIN_STATE_MOVING_UP:
		vy = -COIN_SPEED;
		break;
	case COIN_STATE_MOVING_DOWN:

		vy = COIN_SPEED;
		break;
	case COIN_STATE_WAITING:
		y = maxY;
		vy = 0;
		break;
	}
}
