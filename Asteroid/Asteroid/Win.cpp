#include "Win.h"
#include "MainGame.h"

void Win::Start(sf::RenderWindow* window)
{
	SEManager = new SoundManager;
	SEManager->InitializeSoundEffect();

	enterKey = false;
	sf::Font* font = new sf::Font();
	font->loadFromFile("visitor1.ttf");
	this->winText = new sf::Text("Level Clear! Press Enter to next level.", *font, 32U);
	this->winText->setFillColor(sf::Color::White);
	this->winText->setOrigin(sf::Vector2f(this->winText->getGlobalBounds().width / 2, this->winText->getGlobalBounds().height / 2));
	this->winText->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));

	SEManager->PlaySoundEffect(WinSound);
}


void Win::Update(sf::RenderWindow* window, float dt, Clock &timer, Clock &ufoTimer)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && enterKey)
	{
		_currentState.SetState(new MainGame());
	}
	enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}


void Win::Render(sf::RenderWindow* window)
{
	window->draw(*this->winText);
}


void Win::Destroy(sf::RenderWindow* window)
{
	delete this->winText;
}
