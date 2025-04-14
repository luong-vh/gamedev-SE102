#include "FireBullet.h"
#include "Game.h"
void CFireBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIRE_BULLET_WIDTH / 2;
	t = y - FIRE_BULLET_HEIGHT / 2;
	r = l + FIRE_BULLET_WIDTH;
	b = t + FIRE_BULLET_HEIGHT;
}

void CFireBullet::Render()
{
	if (state == FIRE_BULLET_STATE_WAITING) return;
	int aniId = state == FIRE_BULLET_STATE_LEFT_SHOOTING ? FIRE_BULLET_ANIMATION_ID_LEFT : FIRE_BULLET_ANIMATION_ID_RIGHT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (state == FIRE_BULLET_STATE_WAITING) return;
	if (isDeleted) return;
	x += vx * dt;
	y += vy * dt;
	
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	float tx, ty;
	tx = x - cx;
	ty = y - cy;

	if (tx < 0 || tx > CGame::GetInstance()->GetBackBufferWidth() ||
		ty < 0 || ty > CGame::GetInstance()->GetBackBufferHeight())
	{
		SetState(FIRE_BULLET_STATE_WAITING);
	}
	LPCOLLISIONEVENT e = CCollision::GetInstance()->SweptAABB(this,dt,mario);
	if (e->WasCollided()) mario->OnGetDamage();
}
void CFireBullet::SetState(int _state)
{
	this->state = _state;
	switch (this->state)
	{
	case FIRE_BULLET_STATE_LEFT_SHOOTING:
		vx = -FIRE_BULLET_SPEED_X;
		break;
	case FIRE_BULLET_STATE_RIGHT_SHOOTING:
		vx = FIRE_BULLET_SPEED_X;
		break;
	case FIRE_BULLET_STATE_WAITING:
		vx = 0;
		break;
	}
}

void CFireBullet::Shoot()
{
	this->SetPosition(start_x, start_y);
	float mx, my;
	mario->GetPosition(mx, my);
	float dx = mx - x;
	float dy = my - y;
	float d = sqrt(dx * dx + dy * dy);
	if (d == 0) return;
	vx = FIRE_BULLET_SPEED_X * dx / d;
	vy = FIRE_BULLET_SPEED_Y * dy / d;
	SetState(vx > 0 ? FIRE_BULLET_STATE_RIGHT_SHOOTING : FIRE_BULLET_STATE_LEFT_SHOOTING);
}
