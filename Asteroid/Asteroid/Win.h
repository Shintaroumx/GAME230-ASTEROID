#pragma once
#include "GameState.h"
#include "SoundManager.h"
class Win : public State
{
public:
	void Start(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window,float dt, Clock &timer, Clock &ufoTimer);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	sf::Text* winText;
	bool enterKey;
    SoundManager *SEManager;
};
