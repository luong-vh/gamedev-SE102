#pragma once

#include "GameObject.h"

#define PIPE_BORDER 2
#define PIPE_CELL_WIDTH 32
#define PIPE_CELL_HEIGHT 16
#define PIPE_HEAD_ID 80000
#define PIPE_BODY_ID 80001
class CPipe : public CGameObject
{
private:
	int height;
	
public:

	CPipe(float x, float y, int height) :CGameObject(x, y)
	{
		this->height = height;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects=NULL){}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsCollidable() { return 1; }
};

typedef CPipe* LPPipe;