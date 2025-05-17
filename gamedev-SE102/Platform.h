#pragma once

#include "GameObject.h"
#include "debug.h"
// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected:
	int length;			
	int thick;	// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	int spriteIdBegin2, spriteIdMiddle2, spriteIdEnd2;

public:
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length, int thick,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end,
		int sprite_id_begin2, int sprite_id_middle2, int sprite_id_end2) :CGameObject(x, y)
	{
		this->length = length;
		this->thick = thick;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		this->spriteIdBegin2 = sprite_id_begin2;
		this->spriteIdMiddle2 = sprite_id_middle2;
		this->spriteIdEnd2 = sprite_id_end2;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();

	int IsDirectionColliable(float nx, float ny);
};

typedef CPlatform* LPPLATFORM;