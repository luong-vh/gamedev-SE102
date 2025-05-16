#pragma once
#include "Brick.h"
#define ID_ANI_CLOUD_BLOCK 12000
class CCloudBlock :
    public CBrick
{
public:
    CCloudBlock(float x, float y) : CBrick(x, y) {}

    void Render();
	virtual int IsDirectionColliable(float nx, float ny)
	{
		if (nx == 0 && ny == -1) return 1;
		return 0;
	}
};

