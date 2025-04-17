#include "QuestionBrick.h"
#include "Coin.h"
#include "SuperMushroom.h"
#include "debug.h"
#include "Mario.h"
#include "PlayScene.h"
#include "SuperLeaf.h"
void CQuestionBrick::Render()
{
	if (item) item->Render();	

	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == QUESTION_BRICK_STATE_NORMAL)
		aniId = ID_ANI_QUESTION_BRICK;
	else
		aniId = ID_ANI_QUESTION_BRICK_HITTED;
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (item)
	{
		item->Update(dt, coObjects);
		if (item->IsDeleted()) item = NULL;
	}
	
	
	if (state == QUESTION_BRICK_STATE_NORMAL || state == QUESTION_BRICK_STATE_HITTED)
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
			SetState(QUESTION_BRICK_STATE_HITTED);
		}
	}
}
void CQuestionBrick::OnMarioHitted(LPCOLLISIONEVENT e)
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
	case QUESTION_BRICK_STATE_HITTED:
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
	float mx, my;
	switch (item_type)
	{
	case QUESTION_BRICK_ITEM_TYPE_COIN:
		item = new CCoin(x, y,COIN_STATE_WAITING);
		break;
	case QUESTION_BRICK_ITEM_TYPE_MUSHROOM:
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetLevel() >= MARIO_LEVEL_BIG)
			item = new CSuperLeaf(x, y, 0);
		else 
		{
			mario->GetPosition(mx, my);
			if (x >= mx)
				item = new CSuperMushroom(x, y, 1);
			else
				item = new CSuperMushroom(x, y, -1);
		}
			
			
		break;
	}
	if (item) item->WakeUp();
}