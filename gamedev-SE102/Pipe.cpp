#include "Pipe.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Mario.h"
#include "Textures.h"
#include "Game.h"
#include "PlayScene.h"
void CPipe::Render()
{
	if (this->height <= 0) return;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdHead)->Draw(x, y);

	for (int i = 1; i < this->height; i++)
	{
		yy += PIPE_CELL_HEIGHT;
		s->Get(this->spriteIdBody)->Draw(x, yy);
	}

	RenderBoundingBox();
}
void CPipe::Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float ml, mt, mr, mb;
	mario->GetBoundingBox(ml, mt, mr, mb);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	if ((mr + PIPE_BORDER > l && mr < l) ||
		(ml>r && ml - PIPE_BORDER <r) ||
		(mb<t && mb + PIPE_BORDER*20 >t && mr >= l - PIPE_BORDER && ml <= r + PIPE_BORDER))
	{
		venusFireTrap->isRisable = false;
	}
	else 
	{
		venusFireTrap->isRisable = true;
	}
	
	
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIPE_CELL_WIDTH/2;
	t = y - PIPE_CELL_HEIGHT / 2;
	r = l + PIPE_CELL_WIDTH;
	b = t + PIPE_CELL_HEIGHT * this->height;
}

void CPipe::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	//RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	//rect.left = 0;
	//rect.top = 0;
	//rect.right = (int)r - (int)l;
	//rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	//float xx = x - this->cellWidth / 2 + rect.right / 2;
	float yy = y + PIPE_CELL_HEIGHT * (this->height - 1) / 2;
	CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, r - l, b - t);
}




