#include "Lives.h"
int live=3;
Lives::Lives(sf::Font &font, unsigned int size) : sf::Text("Lives: 3", font, size)
{

}

void Lives::RemoveLife()
{
	live -= 1;
}

int Lives::Value()
{
	return live;
}

void Lives::Update()
{
	this->setString("Lives: " + std::to_string(live));
}