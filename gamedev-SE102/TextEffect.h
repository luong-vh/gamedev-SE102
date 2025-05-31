#pragma once
#include "GameObject.h"
class CTextEffect :
    public CGameObject
{
    int idAni;
public:
    CTextEffect(float x, float y, int aniId) :CGameObject(x, y) {
        this->idAni = aniId;
    }
	void Render() override
	{
		CAnimations::GetInstance()->Get(idAni)->Render(x, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override
	{
		
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	}
};

