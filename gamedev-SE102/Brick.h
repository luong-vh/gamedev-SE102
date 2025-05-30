#pragma once

#include "GameObject.h"
#include "Animations.h"
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define ID_BRICK 0
#define ID_WOODEN_BLOCK 1
#define ID_CLOUD_BLOCK 2
#define ID_GOLDEN_BRICK 3
#define ID_BUTTON_BRICK 4
#define ID_GOAL_CARD 5

#define ID_ANI_BRICK 16000
class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	void Render() {
		CAnimations::GetInstance()->Get(ID_ANI_BRICK)->Render(x,y);
	}
};