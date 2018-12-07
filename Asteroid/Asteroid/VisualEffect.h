#pragma once
#include "GameObject.h"

#define ShipExplode 0
#define RockExplode 1

class VisualEffect : 
	public GameObject
{
public:
	VisualEffect(int type, Texture* t1, Texture* t2,GameObject* obj);
	Clock lifetime;
	float x, y, dx, dy, R, angle;

};
