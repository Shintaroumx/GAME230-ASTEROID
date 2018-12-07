#pragma once
#include "GameObject.h"
#include "Spaceship.h"

using namespace sf;

class UFO:
	public GameObject
{
public:
	UFO(GameObject* obj);
	~UFO();
	virtual void UpdateStatus(float dt);
	bool checkCollisionWith(GameObject * obj);
	Vector2f pos = Vector2f(0, 0);
	float rotation;

private:
	Texture tex;
	sf::Vector2f direction;
};

