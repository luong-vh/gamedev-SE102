#include "Venus_Pipe.h"

void CVenus_Pipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float ml, mt, mr, mb;
	mario->GetBoundingBox(ml, mt, mr, mb);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	if ((mr + PIPE_BORDER > l && mr < l) ||
		(ml > r && ml - PIPE_BORDER < r) ||
		(mb<t && mb + PIPE_BORDER * 20 >t && mr >= l - PIPE_BORDER && ml <= r + PIPE_BORDER))
	{
		venusFireTrap->isRisable = false;
	}
	else
	{
		venusFireTrap->isRisable = true;
	}
}
