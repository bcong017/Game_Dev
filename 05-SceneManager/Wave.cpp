#include "Wave.h"

void Wave::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BIG_WAVE)->Render(x, y);
	animations->Get(ID_ANI_SMALL_WAVE)->Render(x, y);

	RenderBoundingBox();
}

void Wave::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}