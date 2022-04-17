#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MAP 90000
#define ID_ANI_BIG_WAVE 61000
#define ID_ANI_SMALL_WAVE 61001

class Map : public CGameObject {
private:
	float x1, y1, x2, y2;

public:
	Map(float x, float y, float xBWave = 0, float yBWave = 0, float xSWave = 0, float ySWave = 0) : CGameObject(x, y)
	{
		x1 = xBWave;
		y1 = yBWave;
		x2 = xSWave;
		y2 = ySWave;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

