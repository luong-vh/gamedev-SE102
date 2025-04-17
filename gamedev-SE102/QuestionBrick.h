#pragma once
#include "Brick.h"
#include "Item.h"

#define ID_ANI_QUESTION_BRICK_HITTED 10000
#define ID_ANI_QUESTION_BRICK 10001

#define QUESTION_BRICK_SPEED 0.1f

#define QUESTION_BRICK_STATE_HITTED 0
#define QUESTION_BRICK_STATE_NORMAL 1
#define QUESTION_BRICK_STATE_MOVING_UP 2
#define QUESTION_BRICK_STATE_MOVING_DOWN 3

#define QUESTION_BRICK_ITEM_TYPE_COIN 0
#define QUESTION_BRICK_ITEM_TYPE_MUSHROOM 1
class CQuestionBrick :public CBrick
{
private:
	float minY, maxY;
	int item_type;
	CItem* item;
public:
	
	CQuestionBrick(float x, float y, int _item) : CBrick(x, y)
	{
		minY = y - BRICK_WIDTH / 2;
		maxY = y;
		item_type = _item;
		SetState(QUESTION_BRICK_STATE_NORMAL);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsBlocking() { return 1; }
	void SpawnItem();
	void OnMarioHitted(LPCOLLISIONEVENT e);
	void SetState(int _state);
};

