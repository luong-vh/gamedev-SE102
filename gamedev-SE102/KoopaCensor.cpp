#include "KoopaCensor.h"
#include "debug.h"

void CKoopaCensor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CENSOR_BBOX_WIDTH / 2;
	top = y - CENSOR_BBOX_HEIGHT / 2;
	right = left + CENSOR_BBOX_WIDTH;
	bottom = top + CENSOR_BBOX_HEIGHT;
}
void CKoopaCensor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == CENSOR_STATE_WAITING)
	{
		return;
	}

	for (int i = 0; i < coObjects->size(); i++) {
		if ((*coObjects)[i]->IsBlocking() == false) continue;
		float l, t, r, b, l1, t1, r1, b1;
		GetBoundingBox(l, t, r, b);
		(*coObjects)[i]->GetBoundingBox(l1, t1, r1, b1);
		if (!(r < l1 || l > r1 || b < t1 || t > b1)) {
			isOnPlatform = true;
			return;
		}
	}
	isOnPlatform = false;
	
}

