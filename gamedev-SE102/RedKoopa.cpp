#include "RedKoopa.h"
#include "debug.h"

void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	censor->SetPosition(x + KOOPA_BBOX_WIDTH / 2 * direction, y);
	
	if (state == KOOPA_STATE_WALKING && isOnPlatform && !censor->IsOnPlatform())
	{
		ReverseDirection();
	}
	CKoopa::Update(dt, coObjects);
	censor->Update(dt, coObjects);
}

void CRedKoopa::Render()
{
	//censor->Render();
	int aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	GetAniId(aniId);
	if (aniId != 0) CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CRedKoopa::RenderWhenMarioPaused()
{
	int aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	GetAniId(aniId);
	if (aniId != 0) CAnimations::GetInstance()->Get(aniId)->RenderCurrentFrame(x, y);
}

void CRedKoopa::GetAniId(int& aniId)
{
	switch (state)
	{
	case KOOPA_STATE_WAITING:
		aniId = 0;
		return;
	case KOOPA_STATE_INSHELL:
		if (isFlipped) aniId = ID_ANI_RED_KOOPA_INSHELL_FLIP;
		else aniId = ID_ANI_RED_KOOPA_INSHELL;
		break;
	case KOOPA_STATE_WALKING:
		if (direction > 0) aniId = ID_ANI_RED_KOOPA_WALKING_RIGHT;
		else aniId = ID_ANI_RED_KOOPA_WALKING_LEFT;
		break;
	case KOOPA_STATE_REVIVING:
		if (isFlipped) aniId = ID_ANI_RED_KOOPA_REVIVING_FLIP;
		else aniId = ID_ANI_RED_KOOPA_REVIVING;
		break;
	case KOOPA_STATE_SPINNING:
		if (isFlipped) aniId = ID_ANI_RED_KOOPA_SPINNING_FLIP;
		else aniId = ID_ANI_RED_KOOPA_SPINNING;
		break;
	case KOOPA_STATE_DIE:
		aniId = ID_ANI_RED_KOOPA_DIE;
		break;
	default:
		break;
	}
}

void CRedKoopa::SetState(int _state)
{
	if (_state == KOOPA_STATE_WALKING) censor->Activate();
	else censor->Deactivate();
	CKoopa::SetState(_state);
}

void CRedKoopa::ReverseDirection()
{
	CKoopa::ReverseDirection();
	censor->SetPosition(x + KOOPA_BBOX_WIDTH / 2 * direction, y);
}
