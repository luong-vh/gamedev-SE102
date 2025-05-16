#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "VenusFireTrap.h"
#include "QuestionBrick.h"
#include "PiranhaPlant.h"
#include "Collision.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "Koopa.h"
#include "GameData.h"
#include "PlayHUD.h"
#include "GoldenBrick.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount64() - kick_start > MARIO_KICK_TIMEOUT) {
		isKicking = false;
		kick_start = -1;
	}

	HandleTailAttack(dt,coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);

	HandleKoopaHold();
	
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<LPVENUSFIRETRAP>(e->obj))
		OnCollisionWithVenus(e);
	else if (dynamic_cast<LPPIRANHAPLANT>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
	{
		CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
		if (e->ny > 0)
		{
			questionBrick->OnMarioHit(e);
		}
	}
	else if (dynamic_cast<CSuperMushroom*>(e->obj))
	{
		SetLevel(this->level + 1);
		(dynamic_cast<CSuperMushroom*>(e->obj))->Delete();
		CGameData::AddScore(1000);
		CPlayHUD::GetInstance()->SetScore(CGameData::score);
	}
	else if (dynamic_cast<CSuperLeaf*>(e->obj))
	{
		SetLevel(this->level + 1);
		(dynamic_cast<CSuperLeaf*>(e->obj))->Delete();
		CGameData::AddScore(1000);
		CPlayHUD::GetInstance()->SetScore(CGameData::score);
	}
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CGoldenBrick*>(e->obj)) {
		if (e->ny > 0) {
			CGoldenBrick* goldenBrick = dynamic_cast<CGoldenBrick*>(e->obj);
			if (goldenBrick->GetState() == GOLDEN_BRICK_STATE_NORMAL) {
				if (level == MARIO_LEVEL_SMALL) goldenBrick->HitByMario();
				else goldenBrick->Break();
			}
		}
		if (e->obj->GetState() == GOLDEN_BRICK_STATE_GOLD) {
			e->obj->Delete();
			CGameData::AddCoin(1);
			CGameData::AddScore(100);
			CPlayHUD::GetInstance()->SetCoin(CGameData::coin);
			CPlayHUD::GetInstance()->SetScore(CGameData::score);
		}
	}

}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->GetStomped();
			CGameData::AddScore(100);
			CPlayHUD::GetInstance()->SetScore(CGameData::score);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				OnGetDamage();
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	if (e->obj->IsCollidable() == 0) return;
	e->obj->Delete();
	CGameData::AddCoin(1);
	CGameData::AddScore(100);
	CPlayHUD::GetInstance()->SetCoin(CGameData::coin);
	CPlayHUD::GetInstance()->SetScore(CGameData::score);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	CVenusFireTrap* venus = dynamic_cast<CVenusFireTrap*>(e->obj);
	if (venus->GetState() != VENUS_DIE_STATE && venus->GetState() != VENUS_HIDE_STATE)
	{
		OnGetDamage();
	}
}

void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	LPPIRANHAPLANT piranha = dynamic_cast<LPPIRANHAPLANT>(e->obj);
	if (piranha->GetState() != PIRANHA_DIE_STATE)
	{
		OnGetDamage();
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (e->ny < 0)
	{
		if (koopa->GetState() != KOOPA_STATE_DIE)
		{
			koopa->GetStomped();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		return;
	}
	
	if ((e->nx != 0 || e->ny >0) &&
		(koopa -> GetState() == KOOPA_STATE_INSHELL ||
		koopa -> GetState() == KOOPA_STATE_REVIVING))
	{
		if (ableToHold)
		{
			HoldKoopa(koopa);
			koopa->BeingHeld();
		}
		else
		{
			koopa->GetKicked(-e->nx);
			isKicking = true;
			kick_start = GetTickCount64();
		}
		
	}
	
	else
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_DIE)
			{
				OnGetDamage();
			}
		}
	}
}

void CMario::HandleTailAttack(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (ableToAttack && level == MARIO_LEVEL_RACOON && isAttacking == false && koopa == NULL) {
		ableToAttack = false;
		isAttacking = true;
		attack_start = GetTickCount64();
		tail->Attack();
	}
	if (isAttacking) {
		if (GetTickCount64() - attack_start > TAIL_ATTACK_TIMEOUT || level != MARIO_LEVEL_RACOON) {
			isAttacking = false;
			attack_start = -1;
			tail->Wait();
		}
		else {
			if (tail == NULL) tail = new CTail(x, y);
			float tx = x, ty = y + TAIL_OFFSET_Y;
			if (GetTickCount64() - attack_start > TAIL_ATTACK_TIMEOUT / 2) {
				if (nx > 0) tx += TAIL_OFFSET_X;
				else tx -= TAIL_OFFSET_X;
			}
			else {
				if (nx > 0) tx -= TAIL_OFFSET_X;
				else tx += TAIL_OFFSET_X;
			}
			tail->SetPosition(tx, ty);
			tail->Update(dt, coObjects);
		}
	}
	else if (tail) tail->SetPosition(x, y);
}

void CMario::HandleKoopaHold()
{
	if (koopa)
	{
		if (koopa->GetState() == KOOPA_STATE_DIE) {
			koopa->isBeingHeld = false;
			koopa = NULL;
			return;
		}

		if (!koopa->isBeingHeld) ReleaseKoopa();
		else if (!ableToHold) {
			koopa->Release(nx);
			koopa = NULL;
			isKicking = true;
			kick_start = GetTickCount64();
		}
		else {
			float offsetX, offsetY;
			GetKoopaOffset(offsetX, offsetY);
			if (nx < 0) offsetX *= -1;
			koopa->SetPosition(x + offsetX, y + offsetY);
			koopa->SetSpeed(vx, vy);
		}
	}
}



void CMario::OnGetDamage()
{
	if (untouchable) return;
	if (level > MARIO_LEVEL_SMALL)
	{
		SetLevel(level - 1);
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	if (isKicking) {
		if (nx > 0) return ID_ANI_MARIO_SMALL_KICK_RIGHT;
		else return ID_ANI_MARIO_SMALL_KICK_LEFT;
	}
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (koopa) 
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_HOLD_LEFT;
		}
		else {
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_FULL_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_FULL_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_LEFT;
			}
		}
		
	}
	else if (vx == 0)
	{
		if (koopa) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT;
		}
		else
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
		}
	}
	else if (vx > 0)
	{
		if (koopa) 
		{
			aniId = ID_ANI_MARIO_SMALL_RUNNING_HOLD_RIGHT;
			if (ax < 0) aniId = ID_ANI_MARIO_SMALL_RUNNING_HOLD_LEFT;
		}
		else 
		{
			if (ax < 0)
				aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
			else if (ax == MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
			else if (ax == MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
		}
		
	}
	else // vx < 0
	{
		if (koopa) 
		{
			aniId = ID_ANI_MARIO_SMALL_RUNNING_HOLD_LEFT;
			if (ax > 0) aniId = ID_ANI_MARIO_SMALL_RUNNING_HOLD_RIGHT;
		}
		else
		{
			if (ax > 0)
				aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
			else if (ax == -MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
			else if (ax == -MARIO_ACCEL_WALK_X)
				aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
		}
	}
	

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRacoon()
{
	if (isAttacking) {
		if (nx > 0) return ID_ANI_MARIO_RACOON_TAIL_ATTACK_RIGHT;
		else return ID_ANI_MARIO_RACOON_TAIL_ATTACK_LEFT;
	}
	if (isKicking) {
		if (nx > 0) return ID_ANI_MARIO_RACOON_KICK_RIGHT;
		else return ID_ANI_MARIO_RACOON_KICK_LEFT;
	}
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (koopa)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_HOLD_LEFT;
		}
		else
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACOON_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_JUMP_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACOON_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_JUMP_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (koopa) {
					if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_RACOON_IDLE_HOLD_LEFT;
				}
				else
				{
					if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (koopa)
				{
					aniId = ID_ANI_MARIO_RACOON_RUNNING_HOLD_RIGHT;
					if (ax < 0) aniId = ID_ANI_MARIO_RACOON_RUNNING_HOLD_LEFT;
				}
				else
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (koopa)
				{
					aniId = ID_ANI_MARIO_RACOON_RUNNING_HOLD_LEFT;
					if (ax > 0) aniId = ID_ANI_MARIO_RACOON_RUNNING_HOLD_RIGHT;
				}
				else
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	if (isKicking) {
		if (nx > 0) return ID_ANI_MARIO_KICK_RIGHT;
		else return ID_ANI_MARIO_KICK_LEFT;
	}
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (koopa)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_HOLD_LEFT;
		}
		else
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_FULL_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_FULL_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (koopa) {
					if (nx > 0)
						aniId = ID_ANI_MARIO_IDLE_HOLD_RIGHT;
					else
						aniId = ID_ANI_MARIO_IDLE_HOLD_LEFT;
				}
				else
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (koopa)
				{
					aniId = ID_ANI_MARIO_RUNNING_HOLD_RIGHT;
					if (ax < 0) aniId = ID_ANI_MARIO_RUNNING_HOLD_LEFT;
				}
				else
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
				
			}
			else // vx < 0
			{
				if (koopa)
				{
					aniId = ID_ANI_MARIO_RUNNING_HOLD_LEFT;
					if (ax > 0) aniId = ID_ANI_MARIO_RUNNING_HOLD_RIGHT;
				}
				else
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();
	animations->Get(aniId)->Render(x, y);
	if (tail) tail->Render();
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetKoopaOffset(float& offsetX, float& offsetY)
{
	if (level == MARIO_LEVEL_SMALL)
	{
		offsetX = SMALL_OFFSET_X;
		offsetY = SMALL_OFFSET_Y;
	}
	else
	{
		offsetX = BIG_OFFSET_X;
		offsetY = BIG_OFFSET_Y;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level>=MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	if (l > MARIO_LEVEL_RACOON) return;

	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (l == 1) {
		idAniTransform = nx>0 ? ID_ANI_MARIO_TRANSFORM_BIG_TO_SMALL_RIGHT : ID_ANI_MARIO_TRANSFORM_BIG_TO_SMALL_LEFT;
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->MarioPause(900);
	}
	else if (l == 2 && level == 1) {
			idAniTransform = nx > 0 ? ID_ANI_MARIO_TRANSFORM_SMALL_TO_BIG_RIGHT : ID_ANI_MARIO_TRANSFORM_SMALL_TO_BIG_LEFT;
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->MarioPause(900);
	}
	else {
		idAniTransform = ID_ANI_MARIO_TRANSFORM_SMOKE;
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->MarioPause(375);
	}
	level = l;
	if (level == MARIO_LEVEL_RACOON && tail == NULL) tail = new CTail(x, y);
}

