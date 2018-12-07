#include "Asteroid.h"

float Asteroid::speed[3] = { 5.0f, 8.0f, 12.0f };
float Asteroid::radius[3] = { 60.0f, 40.0f, 20.0f };

Asteroid::Asteroid(int level,float spd) :
	level(level) {
	tag = "Asteroid";
	int angle = rand() % 360;
	direction = sf::Vector2f(cos(angle * DEG2RAD), sin(angle * DEG2RAD))*spd;
	tex.loadFromFile("Asteroid.png");
	int x = rand() % 1400;
	int y = rand() % 900;
	sf::Vector2f position(x, y);
	shape.setPosition(position);
	shape.setRadius(radius[level]);
	shape.setOrigin(radius[level], radius[level]);
	shape.setTexture(&tex);
}


Asteroid::Asteroid(sf::Vector2f position, float angle, int level,float spd) :
	level(level) {
	tag = "Asteroid";
	direction = sf::Vector2f(cos(angle * DEG2RAD), sin(angle * DEG2RAD))*spd;
	tex.loadFromFile("Asteroid.png");
	shape.setPosition(position);
	shape.setRadius(radius[level]);
	shape.setOrigin(radius[level], radius[level]);
	shape.setTexture(&tex);
}


Asteroid::~Asteroid() {
}


void Asteroid::UpdateStatus(float dt) {
	if (!isAlive) return;

	distance = direction * speed[level] * dt * 5.0f;
	shape.move(distance);

	sf::Vector2f position = shape.getPosition();
	if (position.x < -radius[level])
		position.x = 1400;
	else if (position.x > 1400)
		position.x = 0.0f;

	if (position.y < -radius[level])
		position.y = 900;
	else if (position.y > 900)
		position.y = 0.0f;
	shape.setPosition(position);
}


//void Asteroid::Draw(RenderWindow &window) {
//	window.draw(shape);
//}


int Asteroid::GetLevel() {
	return level;
}


void Asteroid::BreakDown() {
	level++;

	if (level > 2) {
		isAlive = false;
		return;
	}

	shape.setRadius(radius[level]);
	shape.setOrigin(radius[level], radius[level]);
	float angle = rand() % 360;
	direction = sf::Vector2f(cos(angle * DEG2RAD), sin(angle * DEG2RAD));
}


bool Asteroid::checkCollisionWith(GameObject* obj) {
	float ax = shape.getPosition().x;
	float ay = shape.getPosition().y;

	float px = obj->getCenter().x;
	float py = obj->getCenter().y;

	Vector2f dir = shape.getPosition() - obj->getCenter();

	float sqrDistance = ((ax - px) * (ax - px)) + ((ay - py) * (ay - py));
	float sqrRadius = (this->shape.getRadius() + obj->shape.getRadius())*(this->shape.getRadius() + obj->shape.getRadius());

	if (sqrDistance <= sqrRadius) {
		if (obj->tag == "Bullet"&&obj->isAlive&&obj->shape.getFillColor()==Color::White) {
			if (isAlive) 
				BreakDown();
		}
		if (obj->tag == "Asteroid") {
			//this->direction = -direction;
			this->direction.x = dir.x / 100;
			this->direction.y = dir.y / 100;
		}
	}

	return (sqrDistance <= sqrRadius);
}


//Vector2f Asteroid::getCenter()
//{
//	return shape.getPosition();
//}
