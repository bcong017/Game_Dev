#include "Background.h"

void Background::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BACKGROUND)->Render(x, y);
	RenderBoundingBox();
}

void Background::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}