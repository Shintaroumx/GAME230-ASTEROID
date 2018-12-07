#pragma once
#include"sfml.h"

using namespace sf;

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void UpdateStatus(float dt);
	virtual int GetLevel();
	virtual bool checkCollisionWith(GameObject * obj);
	void Draw(RenderWindow* window);
	Vector2f getCenter();
	bool isAlive=true;
	CircleShape shape;
	std::string tag;

private:

};

