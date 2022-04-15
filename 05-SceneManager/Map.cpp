#include "Map.h"

void Map::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MAP)->Render(x, y);
	RenderBoundingBox();
}

void Map::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}