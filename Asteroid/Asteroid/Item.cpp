#include "Item.h"

Item::Item(GameObject* obj,Color clr)
{
	tex.loadFromFile("item.png");
	shape.setTexture(&tex);
	shape.setPosition(obj->shape.getPosition());
	shape.setOrigin(20, 20);
	shape.setRadius(20);
	shape.setFillColor(clr);
	if(clr==Color::Green)
	    tag = "Shield";
	if (clr == Color::Red)
		tag = "RapidShoot";
	if (clr == Color::White)
		tag = "Invincible";
}

Item::~Item()
{
}



void Item::UpdateStatus(float dt)
{


	pos = shape.getPosition();
	if (pos.x < -10.0f)
		pos.x = 1400;
	else if (pos.x > 1400)
		pos.x = 0.0f;
	if (pos.y < -10.0f)
		pos.y = 900;
	else if (pos.y > 900)
		pos.y = 0.0f;
	shape.setPosition(pos);
}


bool Item::checkCollisionWith(GameObject* obj) {
	float ax = shape.getPosition().x;
	float ay = shape.getPosition().y;

	float px = obj->getCenter().x;
	float py = obj->getCenter().y;

	Vector2f dir = shape.getPosition() - obj->getCenter();

	float sqrDistance = ((ax - px) * (ax - px)) + ((ay - py) * (ay - py));
	float sqrRadius = (this->shape.getRadius() + obj->shape.getRadius())*(this->shape.getRadius() + obj->shape.getRadius());

	return (sqrDistance <= sqrRadius);
}