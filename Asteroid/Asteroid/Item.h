#pragma once
#include "GameObject.h"
#include "Asteroid.h"

using namespace sf;

class Item :
	public GameObject
{
public:
	Item(GameObject* obj, Color clr);
	~Item();
	virtual void UpdateStatus(float dt);
	bool checkCollisionWith(GameObject * obj);
	Vector2f pos = Vector2f(0, 0);
	float rotation;

private:
	Texture tex;
};

