#pragma once
#include "GameObject.h"
#include "Asteroid.h"

using namespace sf;

class Spaceship :
	public GameObject
{
public:
	Spaceship();
	~Spaceship();
	virtual void UpdateStatus(float dt);
	bool checkCollisionWith(GameObject * obj);
	//virtual void Draw(RenderWindow &window);
	//virtual Vector2f getCenter();
	Vector2f pos = Vector2f(0, 0);
	float rotation;

private:
	Texture tex;
	//CircleShape shape;
	Vector2f vel=Vector2f(0, 0);
	float accel=0;
	float max_speed = 2.0f;
};



