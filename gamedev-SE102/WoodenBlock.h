#pragma once
#include "Brick.h"
#define ID_ANI_WOODEN_BLOCK 11000
class CWoodenBlock :
    public CBrick
{
public:
    CWoodenBlock(float x, float y) : CBrick(x, y) {}

    void Render();
};

