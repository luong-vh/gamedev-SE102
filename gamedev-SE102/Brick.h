#pragma once

#include "GameObject.h"

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define ID_BRICK 0
#define ID_WOODEN_BLOCK 1
#define ID_CLOUD_BLOCK 2
#define ID_GOLDEN_BRICK 3
class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
};