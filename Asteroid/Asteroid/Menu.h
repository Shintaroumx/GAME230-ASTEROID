#pragma once
#include "GameState.h"
#include "main.h"
#include "SoundManager.h"

class Menu : public State
{
public:
	void Start(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, float dt, Clock &timer, Clock &ufoTimer);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	sf::Font* font;
	sf::Text* title;
	sf::Text* usingKeyboard;
	sf::Text* quit;
	SoundManager *SEManager;
	int selected;

	bool upKey, downKey;
};