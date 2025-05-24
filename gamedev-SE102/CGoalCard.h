#pragma once
#include "Brick.h"
#include "GameObject.h"
#define GOAL_CARD_BBOX_WIDTH 24
#define GOAL_CARD_BBOX_HEIGHT 28
#define GOAL_CARD_NORMAL 0
#define GOAL_CARD_HIT 1
#define ID_ANI_GOAL_CARD_NORMAL 15001
#define ID_ANI_GOAL_CARD_HIT 15000
class CGoalCard :
    public CGameObject
{
public:
    CGoalCard(float x, float y) : CGameObject(x,y)
    {
        SetState(GOAL_CARD_NORMAL);
    }
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int IsBlocking() { return 1; }
    void Render();
    void HitByMario();
    void HitByKoopa();
};

