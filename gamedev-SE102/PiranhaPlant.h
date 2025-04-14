#pragma once
#include "GameObject.h"

#define PIRANHA_RISE_STATE 0
#define PIRANHA_DIVE_STATE 1000
#define PIRANHA_HIDE_STATE 2000
#define PIRANHA_DIE_STATE 3000
#define PIRANHA_ATTACK_STATE 4000
#define PIRANHA_CELL_HEIGHT 8
#define PIRANHA_CELL_WIDTH 16


#define PIRANHA_ANIMATION_ID 120000
#define PIRANHA_SPEED 0.03f
#define PIRANHA_DIE_TIMEOUT 500
#define PIRANHA_HIDE_TIMEOUT 1000
#define PIRANHA_ATTACK_TIMEOUT 1000
class CPiranha_Pipe;
typedef CPiranha_Pipe* LPPiranhaPipe;

class CPiranhaPlant :
    public CGameObject
{
private:
	ULONGLONG state_start;
	int height;
	float minY, maxY;
	
public:
	bool isRisable;
	LPPiranhaPipe pipe;
	CPiranhaPlant(float x, float y,
		int height,
		LPPiranhaPipe _pipe) : CGameObject(x, y)
	{
		
		isRisable = true;
		state_start = -1;
		this->height = height;
		this->pipe = _pipe;
		this->minY = y;
		this->maxY = y + height * PIRANHA_CELL_HEIGHT;
		SetState(PIRANHA_HIDE_STATE);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; };
};
typedef CPiranhaPlant* LPPiranhaPlant;


