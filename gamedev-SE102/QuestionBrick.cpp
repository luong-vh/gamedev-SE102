#include "QuestionBrick.h"
#include "Coin.h"
#include "SuperMushroom.h"
#include "debug.h"
#include "Mario.h"
#include "PlayScene.h"
#include "SuperLeaf.h"
#include "OneUpMushroom.h"
void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == QUESTION_BRICK_STATE_NORMAL)
		aniId = ID_ANI_QUESTION_BRICK;
	else
		aniId = ID_ANI_QUESTION_BRICK_HIT;
	animations->Get(aniId)->Render(x, y);
}
void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	
	if (state == QUESTION_BRICK_STATE_NORMAL || state == QUESTION_BRICK_STATE_HIT)
		return;
	y += vy * dt;
	if (state == QUESTION_BRICK_STATE_MOVING_UP)
	{
		if (y <= minY)
		{
			y = minY;
			SetState(QUESTION_BRICK_STATE_MOVING_DOWN);
		}
	}
	else if (state == QUESTION_BRICK_STATE_MOVING_DOWN)
	{
		if (y >= maxY)
		{
			y = maxY;
			SetState(QUESTION_BRICK_STATE_HIT);
		}
	}
}
void CQuestionBrick::OnMarioHit(LPCOLLISIONEVENT e)
{
	if ( state == QUESTION_BRICK_STATE_NORMAL) {
		SetState(QUESTION_BRICK_STATE_MOVING_UP);
		SpawnItem();
	}
}
void CQuestionBrick::SetState(int _state)
{
	CGameObject::SetState(_state);
	switch (_state)
	{
	case QUESTION_BRICK_STATE_HIT:
		vy = 0;
		break;
	case QUESTION_BRICK_STATE_MOVING_UP:
		vy = -QUESTION_BRICK_SPEED;
		break;
	case QUESTION_BRICK_STATE_MOVING_DOWN:
		vy = QUESTION_BRICK_SPEED;
		break;
	case QUESTION_BRICK_STATE_NORMAL:
		vy = 0;
		break;
	default:
		break;
	}
}
void CQuestionBrick::SpawnItem()
{
	CItem* item = NULL;
	float mx, my;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (item_type)
	{
	case QUESTION_BRICK_ITEM_TYPE_COIN:
		item = new CCoin(x, y,COIN_STATE_WAITING);
		break;
	case QUESTION_BRICK_ITEM_TYPE_MUSHROOM:
		
		if (mario->GetLevel() >= MARIO_LEVEL_BIG)
			item = new CSuperLeaf(x, y - BRICK_BBOX_HEIGHT, 0);
		else 
		{
			mario->GetPosition(mx, my);
			if (x >= mx)
				item = new CSuperMushroom(x, y - BRICK_BBOX_HEIGHT, 1);
			else
				item = new CSuperMushroom(x, y - BRICK_BBOX_HEIGHT, -1);
		}
		break;
	case QUESTION_BRICK_ITEM_TYPE_ONEUP:
		mario->GetPosition(mx, my);
		if (x >= mx)
			item = new COneUpMushroom(x, y - BRICK_BBOX_HEIGHT, 1);
		else
			item = new COneUpMushroom(x, y - BRICK_BBOX_HEIGHT, -1);
		break;

	}
	
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
	item->WakeUp();
}