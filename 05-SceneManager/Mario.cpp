#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Crab.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	/*if (abs(vx) > abs(maxVx)) vx = maxVx;*/

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);


}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
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

	if (dynamic_cast<CCrab*>(e->obj))
		OnCollisionWithGoomba(e);
	
	
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CCrab* goomba = dynamic_cast<CCrab*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	//if (e->ny < 0)
	//{
	//	if (goomba->GetState() != GOOMBA_STATE_DIE)
	//	{
	//		goomba->SetState(GOOMBA_STATE_DIE);
	//		vy = -MARIO_JUMP_DEFLECT_SPEED;
	//	}
	//}
	//else // hit by Goomba
	//{
	//	if (untouchable == 0)
	//	{
	//		if (goomba->GetState() != GOOMBA_STATE_DIE)
	//		{
	//			if (level > MARIO_LEVEL_SMALL)
	//			{
	//				level = MARIO_LEVEL_SMALL;
	//				StartUntouchable();
	//			}
	//			else
	//			{
	//				DebugOut(L">>> Mario DIE >>> \n");
	//				SetState(MARIO_STATE_DIE);
	//			}
	//		}
	//	}
	//}
	SetState(MARIO_STATE_DIE);
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (nx >= 0)
			aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
		else
			aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
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
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				aniId = ID_ANI_MARIO_WALKING_LEFT;
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
	else
		aniId = GetAniIdBig();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform)
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
		/*vy = -MARIO_JUMP_DEFLECT_SPEED;*/
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isSitting)
	{
		left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
		top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
		right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
		bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
	}
	else if (state == MARIO_STATE_DIE)
	{
		left = x - MARIO_BBOX_DIE_WIDTH / 2;
		top = y - MARIO_BBOX_DIE_HEIGHT / 2;
		right = left + MARIO_BBOX_DIE_WIDTH;
		bottom = top + MARIO_BBOX_DIE_HEIGHT;
	}
	else 
	{
		left = x - MARIO_BIG_BBOX_WIDTH/2;
		top = y - MARIO_BIG_BBOX_HEIGHT/2;
		right = left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
	}
}


