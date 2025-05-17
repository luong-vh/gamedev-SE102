#pragma once
#include "Block.h"

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CBlock : public CGameObject
{
private:
	bool hasBottomShadow;
	float cellWidth, cellHeight;
	int width, height;
	int cellId1, cellId2, cellId3, cellId4, cellId5, cellId6, cellId7, cellId8, cellId9;
	int shadowCellId, leftShadowCellId, bottomShadowCellId1, bottomShadowCellId2;
public:
	CBlock(float x, float y,
		float cell_width, float cell_height, int _width, int _height,
		int cell_id_1,
		int shadow_cell_id,
		bool has ) : CGameObject(x, y) 
	{
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->width = _width;
		this->height = _height;
		this->cellId1 = cell_id_1;
		this->cellId2 = cell_id_1 + 1;
		this->cellId3 = cell_id_1 + 2;
		this->cellId4 = cell_id_1 + 3;
		this->cellId5 = cell_id_1 + 4;
		this->cellId6 = cell_id_1 + 5;
		this->cellId7 = cell_id_1 + 6;
		this->cellId8 = cell_id_1 + 7;
		this->cellId9 = cell_id_1 + 8;
		this->shadowCellId = shadow_cell_id;
		this->leftShadowCellId = shadow_cell_id + 1;
		this->bottomShadowCellId1 = shadow_cell_id + 2;
		this->bottomShadowCellId2 = shadow_cell_id + 3;

		hasBottomShadow = has;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsDirectionColliable(float nx, float ny) 
	{ 
		if (nx == 0 && ny == -1) return 1;
		return 0;
	}
};

