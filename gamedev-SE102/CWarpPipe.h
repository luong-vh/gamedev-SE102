#pragma once
#include "Pipe.h"
#include "Mario.h"
#define PIPE_STATE_DOWN 0
#define PIPE_STATE_UP 1
#define WARP_TIME 500
class CWarpPipe :
    public CPipe
{
    bool isWarping;
    float warpTime;

public:
    CWarpPipe(float x, float y, int height, int state) : CPipe(x, y, height) {
        this->state = state;
        isWarping = false;
    }
    CWarpPipe(float x, float y, int height, int headId, int bodyId, int state) :CPipe(x, y, height, headId, bodyId) {
        this->state = state;
        isWarping = false;
    }
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    void HandleWithMario(LPCOLLISIONEVENT e, CMario* mario);
};

