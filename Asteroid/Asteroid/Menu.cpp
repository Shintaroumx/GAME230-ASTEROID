#include <iostream>
#include "Menu.h"
#include "MainGame.h"
int levelIndex;
void Menu::Start(sf::RenderWindow* window)
{
	SEManager = new SoundManager;
	SEManager->InitializeSoundEffect();

	score = 0;
	live = 3;
	levelIndex = 1;

	this->selected = 0;

	this->font = new Font();
	this->font->loadFromFile("visitor1.ttf");

	this->title = new Text("Asteroid", *this->font, 128U);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	this->title->setPosition(window->getSize().x / 2, window->getSize().y / 4);

	this->usingKeyboard = new Text(">Play", *this->font, 32U);
	this->usingKeyboard->setOrigin(this->title->getGlobalBounds().width / 8, this->title->getGlobalBounds().height / 2);
	this->usingKeyboard->setPosition(window->getSize().x / 2, window->getSize().y / 2);


	this->quit = new Text(">Exit", *this->font, 32U);
	this->quit->setOrigin(this->title->getGlobalBounds().width / 8, this->title->getGlobalBounds().height / 2);
	this->quit->setPosition(window->getSize().x / 2, window->getSize().y / 2 + 50);


}
void Menu::Update(sf::RenderWindow* window, float dt, Clock &timer, Clock &ufoTimer)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !this->upKey)
	{
		this->selected -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !this->downKey)
	{
		this->selected += 1;
	}
	if (this->selected > 1)
	{
		this->selected = 0;
	}
	if (this->selected < 0)
	{
		this->selected = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		switch (this->selected)
		{
		case 0:
			_currentState.SetState(new MainGame());
			break;
		case 1:
			quitGame = true;
			break;

		}
	}
	this->upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	this->downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
}
void Menu::Render(sf::RenderWindow* window)
{
	this->usingKeyboard->setFillColor(Color::White);
	this->quit->setFillColor(Color::White);

	switch (this->selected)
	{
	case 0:
		this->usingKeyboard->setFillColor(Color::Red);
		break;
	case 1:
		this->quit->setFillColor(Color::Red);
		break;
	}
	window->draw(*this->title);
	window->draw(*this->usingKeyboard);
	window->draw(*this->quit);
}
void Menu::Destroy(sf::RenderWindow* window)
{
	delete this->font;
	delete this->title;
	delete this->usingKeyboard;
	delete this->quit;
}
