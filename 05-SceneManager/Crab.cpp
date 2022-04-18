#include "Crab.h"
#include "Mario.h"

#include "debug.h"

CCrab::CCrab(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_IDLE);
}

void CCrab::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH_DIE/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH_DIE;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CCrab::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

};

void CCrab::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CCrab*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	if (e->nx != 0)
	{
		/*vx = -vx;*/
	}
}

void CCrab::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	float xx, yy;
	CMario::GetInstance()->GetPosition(xx, yy);
	
	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}						

	if (abs(xx - x) <= 100 && state != GOOMBA_STATE_DIE)
		SetState(GOOMBA_STATE_WALKING);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CCrab::Render()
{
	int aniId = -1;
	if (vx == 0)
		aniId = ID_ANI_GOOMBA_IDLE;
	else
		aniId = ID_ANI_GOOMBA_WALKING;
	
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
}

void CCrab::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			float xx, yy;
			CMario::GetInstance()->GetPosition(xx, yy);
			if (x > xx)
			{
				vx = -GOOMBA_WALKING_SPEED;
			}
			else
				vx = GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_IDLE:
			ax = 0;
			vx = 0;
			break;
	}
}
