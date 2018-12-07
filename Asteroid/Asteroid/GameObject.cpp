#include "GameObject.h"

GameObject::~GameObject()
{
}

GameObject::GameObject()
{
}

 
void GameObject::UpdateStatus(float dt) 
{
}

int GameObject::GetLevel()
{
	return 0;
}

void GameObject::Draw(RenderWindow* window)
{
	window->draw(shape);
}

Vector2f GameObject::getCenter()
{
	return shape.getPosition();
}

bool GameObject::checkCollisionWith(GameObject* obj)
{
	return false;
}
