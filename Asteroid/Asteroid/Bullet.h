#pragma once
#include "GameObject.h"
#include"Spaceship.h"
#include <list>

using namespace sf;

class Bullet :
	public GameObject
{
public:
	Bullet();
	~Bullet();

	void SetBullet(Spaceship &ship, Color clr,GameObject* obj);
	virtual void UpdateStatus(float dt);
	//virtual void Draw(RenderWindow &window);
	//virtual Vector2f getCenter();
	Clock lifetime;

private:
	Vector2f forward;
	Vector2f vel;

};

