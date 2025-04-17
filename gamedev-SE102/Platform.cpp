#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"
#include "Game.h"

void CPlatform::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + (r-l) / 2;
	float yy = y - this->cellHeight / 2 + (b - t) / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, r-l, b-t);
}

void CPlatform::Render()
{
	if (this->length <= 0 || this->thick <= 0) return; 
	float xx = x; 
	float yy = y;
	CSprites * s = CSprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw(xx, yy);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (length>1)
		s->Get(this->spriteIdEnd)->Draw(xx, yy);
	for (int i = 1; i < this->thick; i++)
	{	
		xx = x;
		yy += this->cellHeight;
		s->Get(this->spriteIdBegin2)->Draw(xx, yy);
		xx += this->cellWidth;
		for (int j = 1; j < this->length - 1; j++)
		{
			s->Get(this->spriteIdMiddle2)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		if (length > 1)
			s->Get(this->spriteIdEnd2)->Draw(xx, yy);
	}
	
	//RenderBoundingBox();
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
	l = x - this->cellWidth / 2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->length;
	b = t + this->cellHeight * this->thick;
}

int CPlatform::IsDirectionColliable(float nx, float ny)
{
	return 1;
}