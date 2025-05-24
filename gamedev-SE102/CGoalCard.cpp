#include "CGoalCard.h"

void CGoalCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GOAL_CARD_BBOX_WIDTH / 2;
	t = y - GOAL_CARD_BBOX_HEIGHT / 2;
	r = l + GOAL_CARD_BBOX_WIDTH;
	b = t + GOAL_CARD_BBOX_HEIGHT;
}

void CGoalCard::Render()
{
	int aniId = ID_ANI_GOAL_CARD_NORMAL;
	if (state == GOAL_CARD_HIT) aniId = ID_ANI_GOAL_CARD_HIT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CGoalCard::HitByMario()
{
}

void CGoalCard::HitByKoopa()
{
}
