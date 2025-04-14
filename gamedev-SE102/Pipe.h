#pragma once

#include "GameObject.h"
#include "VenusFireTrap.h"
#define PIPE_BORDER 5
#define PIPE_CELL_WIDTH 32
#define PIPE_CELL_HEIGHT 16
class CPipe : public CGameObject
{
private:
	int height;
	int spriteIdHead, spriteIdBody;
	
public:
	LPVENUSFIRETRAP venusFireTrap;
	CPipe(float x, float y,
		int height,
		int spriteIdHead, int spriteIdBody, LPVENUSFIRETRAP venus) :CGameObject(x, y)
	{
		this->height = height;
		this->spriteIdHead = spriteIdHead;
		this->spriteIdBody = spriteIdBody;
		this->venusFireTrap = venus;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects=NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();

	int IsCollidable() { return 1; }
};

typedef CPipe* LPPipe;