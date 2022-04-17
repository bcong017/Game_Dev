#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BACKGROUND 95000

class Background: public CGameObject {
private:
	float x1, y1, x2, y2;
public:
	Background(float x, float y, float xBWave = 0, float yBWave = 0, float xSWave = 0, float ySWave = 0) : CGameObject(x, y) 
	{
		x1 = xBWave;
		y1 = xBWave;
		x2 = xSWave;
		y2 = ySWave;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};


