#define NOMINMAX
#include <windows.h>
#include "GameState.h"
#include "Menu.h"
#include "main.h"
CurrentState _currentState;
bool quitGame = false;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1400, 900), "Asteriod");
	Clock clock;
	Clock timer;
	Clock ufoTimer;

	_currentState.SetWindow(&window);
	_currentState.SetState(new Menu());

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float dt = clock.restart().asSeconds();
		window.clear(sf::Color::Black);

		_currentState.Update(dt,timer, ufoTimer);
		_currentState.Render();

		window.display();

		if (quitGame)
		{
			window.close();
		}

		Sleep(5);
	}

	return 0;
}
