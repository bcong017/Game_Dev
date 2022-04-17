#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BIG_WAVE 61000
#define ID_ANI_SMALL_WAVE 61001

class Wave : public CGameObject {
public:
	Wave(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};


