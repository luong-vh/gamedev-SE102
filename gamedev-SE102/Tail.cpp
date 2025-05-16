#include "Tail.h"
#include "debug.h"
#include "Koopa.h"
#include "Goomba.h"
#include "PiranhaPlant.h"
#include "VenusFireTrap.h"
#include "GoldenBrick.h"
#include "ButtonBrick.h"
void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - TAIL_BBOX_WIDTH / 2;
    top = y - TAIL_BBOX_HEIGHT / 2;
    right = left + TAIL_BBOX_WIDTH;
    bottom = top + TAIL_BBOX_HEIGHT;
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (state == TAIL_STATE_WAITING) return;
	CheckOverlap(coObjects);    
}

void CTail::CheckOverlap(vector<LPGAMEOBJECT>* coObjects)
{
    for (int i = 0; i < coObjects->size(); i++) {
		float l, t, r, b, l1, t1, r1, b1;
		GetBoundingBox(l, t, r, b);
		(*coObjects)[i]->GetBoundingBox(l1, t1, r1, b1);
        if (!(r < l1 || l > r1 || b < t1 || t > b1)) {
            OnOverlapWith((*coObjects)[i]);
        }
    }
}

void CTail::OnOverlapWith(LPGAMEOBJECT obj)
{
	if (dynamic_cast<CKoopa*>(obj)) {
		CKoopa* koopa = dynamic_cast<CKoopa*>(obj);
		if (koopa->GetState() != KOOPA_STATE_DIE) {
			float kx, ky;
			koopa->GetPosition(kx, ky);
			int direction = 1;
			if (x > kx) direction = -1;
			koopa->GetTailHit(direction);
		}
	}
	else if (dynamic_cast<CGoomba*>(obj)) {
		CGoomba* goomba = dynamic_cast<CGoomba*>(obj);
		if (goomba->GetState() != GOOMBA_STATE_DIE) {
			float kx, ky;
			goomba->GetPosition(kx, ky);
			int direction = 1;
			if (x > kx) direction = -1;
			goomba->GetTailHit(direction);
		}
	}
	else if (dynamic_cast<CPiranhaPlant*>(obj)) {
		CPiranhaPlant* piranha = dynamic_cast<CPiranhaPlant*>(obj);
		if (piranha->GetState() != PIRANHA_DIE_STATE) {
			piranha->HitByTail();
		}
	}
	else if (dynamic_cast<CVenusFireTrap*>(obj)) {
		CVenusFireTrap* venus = dynamic_cast<CVenusFireTrap*>(obj);
		if (venus->GetState() != VENUS_DIE_STATE) {
			venus->HitByTail();
		}
	}
	else if (dynamic_cast<CGoldenBrick*>(obj)) {
		CGoldenBrick* goldenBrick = dynamic_cast<CGoldenBrick*>(obj);
		if (goldenBrick->GetState() == GOLDEN_BRICK_STATE_NORMAL) {
			goldenBrick->Break();
		}
	}
	else if (dynamic_cast<CButtonBrick*>(obj)) {
		CButtonBrick* buttonBrick = dynamic_cast<CButtonBrick*>(obj);
		if (buttonBrick->GetState() == BUTTON_BRICK_STATE_NORMAL) {
			buttonBrick->SetState(BUTTON_BRICK_STATE_MOVE_UP);
		}
	}
	
}
