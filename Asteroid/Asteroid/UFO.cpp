#include "UFO.h"

UFO::UFO(GameObject* obj)
{
	tex.loadFromFile("UFO.png");
	shape.setTexture(&tex);
	shape.setPosition(rand()%1400, rand()%900);
	shape.setOrigin(20, 20);
	shape.setRadius(20);
	tag = "UFO";
	direction = Vector2f(10, 7);
}

UFO::~UFO()
{
}



void UFO::UpdateStatus(float dt)
{
	Vector2f distance = direction * dt * 4.0f;
	shape.move(distance);

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


bool UFO::checkCollisionWith(GameObject* obj) {
	float ax = shape.getPosition().x;
	float ay = shape.getPosition().y;

	float px = obj->getCenter().x;
	float py = obj->getCenter().y;

	Vector2f dir = shape.getPosition() - obj->getCenter();

	float sqrDistance = ((ax - px) * (ax - px)) + ((ay - py) * (ay - py));
	float sqrRadius = (this->shape.getRadius() + obj->shape.getRadius())*(this->shape.getRadius() + obj->shape.getRadius());

	return (sqrDistance <= sqrRadius);
}