#include "Map.h"

void Map::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MAP)->Render(x, y);
	animations->Get(ID_ANI_BIG_WAVE)->Render(x1, y1);
	animations->Get(ID_ANI_SMALL_WAVE)->Render(x2, y2);
	RenderBoundingBox();
}

void Map::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}