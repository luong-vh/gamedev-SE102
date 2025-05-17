#include "Block.h"

void CBlock::Render()
{
	if (width <= 0 || height <= 0) return;

	float xx = x;
	float yy = y;

	CSprites* s = CSprites::GetInstance();

	s->Get(this->cellId1)->Draw(x, y);

	LPSPRITE sprite = s->Get(this->cellId2);
	for (int i = 1; i < this->width - 1; i++)
	{
		sprite->Draw(x + i*cellWidth , y);
		
	}
	s->Get(this->cellId3)->Draw(x + cellWidth*(width-1), y);

	
	sprite = s->Get(this->cellId5);
	for (int t = 1; t < this->height - 1; t++)
	{
		s->Get(this->cellId4)->Draw(x, y + t * cellHeight);
		s->Get(this->cellId6)->Draw(x + cellWidth * (width - 1), y + t * cellHeight);
		for (int j = 1; j < this->width - 1; j++)
		{
			sprite->Draw(x + j * cellWidth, y + t * cellHeight);
		}
	}
	
	s->Get(this->cellId7)->Draw(x, y + cellHeight * (height - 1));

	for (int i = 1; i < this->width - 1; i++)
	{
		s->Get(cellId8)->Draw(x + i * cellWidth, y + cellHeight * (height - 1));
	}

	s->Get(this->cellId9)->Draw(x + cellWidth * (width - 1), y + cellHeight * (height - 1));

	s->Get(leftShadowCellId)->Draw(x + cellWidth * width, y + cellHeight);
	
	for (int i = 2; i < height; i++)
	{
		s->Get(shadowCellId)->Draw(x + cellWidth * width, y + cellHeight * i);
	}
	if (hasBottomShadow)
	{
		s->Get(bottomShadowCellId1)->Draw(x + cellWidth , y + cellHeight * height );
		s->Get(bottomShadowCellId2)->Draw(x + cellWidth * width, y + cellHeight * height);
		for (int i = 2; i < width; i++)
		{
			s->Get(shadowCellId)->Draw(x + cellWidth * i, y + cellHeight * height);
		}
	}

}

void CBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - cellWidth / 2;
	t = y - cellHeight / 2;
	r = l + cellWidth * width;
	b = t + cellHeight /* * height*/;
}
