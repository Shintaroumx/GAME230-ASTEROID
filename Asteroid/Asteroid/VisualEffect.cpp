#include "VisualEffect.h"

VisualEffect::VisualEffect(int type, Texture* t1, Texture* t2, GameObject* obj)
{
	tag = "Explosion";
	shape.setRadius(15);
	shape.setOrigin(15, 15);
	if (type == ShipExplode)
	{
		shape.setTexture(t1);
	}
	else if (type == RockExplode)
	{
		shape.setTexture(t2);
	}
	shape.setPosition(obj->getCenter());
}

