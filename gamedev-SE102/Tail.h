#pragma once
#include "GameObject.h"

#define TAIL_STATE_WAITING 0
#define TAIL_STATE_ATTACKING 1

#define TAIL_BBOX_WIDTH 10
#define TAIL_BBOX_HEIGHT 3

#define TAIL_ATTACK_TIMEOUT 300
class CTail :
    public CGameObject
{
protected:
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }

    void GetBoundingBox(float& left, float& top, float& right, float& bottom);

public:
    CTail(float x, float y) : CGameObject(x, y) 
    {
		SetState(TAIL_STATE_WAITING);
    }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render() {
        RenderBoundingBox(); 
    }
    virtual void CheckOverlap(vector<LPGAMEOBJECT>* coObjects);
    virtual void OnOverlapWith(LPGAMEOBJECT obj);
	virtual void Attack() {
		SetState(TAIL_STATE_ATTACKING);
	}
	virtual void Wait() {
		SetState(TAIL_STATE_WAITING);
	}


};

