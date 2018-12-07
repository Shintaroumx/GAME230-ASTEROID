#include "Spaceship.h"

Spaceship::Spaceship()
{
	tex.loadFromFile("spaceship.png");
	shape.setTexture(&tex);
	shape.setPosition(750, 450);
	shape.setOrigin(20, 20);
	shape.setRadius(20);
	tag = "Spaceship";
}

Spaceship::~Spaceship()
{
}



void Spaceship::UpdateStatus(float dt) 
{
	rotation = shape.getRotation();
	float x_speed = cos(rotation * DEG2RAD)*50;
	float y_speed = sin(rotation * DEG2RAD)*50;

	vel.x +=  accel * dt * (x_speed / 10);
	vel.y +=  accel * dt * (y_speed / 10);

	if ((vel.x * vel.x) > (max_speed * max_speed))
		vel.x = vel.x > 0 ? max_speed : -max_speed;
	if ((vel.y * vel.y) > (max_speed * max_speed))
		vel.y = vel.y > 0 ? max_speed : -max_speed;
	shape.move(vel);

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		accel = 1;
	}
	else {
		accel = 0;
		if (vel.x > 0)
			vel.x -= dt;
		if (vel.x < 0)
			vel.x +=dt;
		if (vel.y > 0)
			vel.y -= dt;
		if (vel.y < 0)
			vel.y += dt;
	}
	

	if (Keyboard::isKeyPressed(Keyboard::Left))
		shape.rotate(-200*dt);
	if (Keyboard::isKeyPressed(Keyboard::Right))
		shape.rotate(200*dt);

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


bool Spaceship::checkCollisionWith(GameObject* obj) {
	float ax = shape.getPosition().x;
	float ay = shape.getPosition().y;

	float px = obj->getCenter().x;
	float py = obj->getCenter().y;

	Vector2f dir = shape.getPosition() - obj->getCenter();

	float sqrDistance = ((ax - px) * (ax - px)) + ((ay - py) * (ay - py));
	float sqrRadius = (this->shape.getRadius() + obj->shape.getRadius())*(this->shape.getRadius() + obj->shape.getRadius());

	return (sqrDistance <= sqrRadius);
}
