#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class State
{
public:
	virtual void Start(RenderWindow* window)
	{
	}

	virtual void Update(RenderWindow* window,float dt,Clock &timer, Clock &ufoTimer)
	{
	}

	virtual void Render(RenderWindow* window)
	{
	}

	virtual void Destroy(RenderWindow* window)
	{
	}
	~State()
	{
	}
};

class CurrentState
{
public:
	CurrentState()
	{
		this->state = NULL;
	}

	void SetWindow(RenderWindow* window)
	{
		this->window = window;
	}

	void SetState(State* state)
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
		}
		this->state = state;
		if (this->state != NULL)
		{
			this->state->Start(this->window);
		}
	}

	void Update(float dt, Clock &timer, Clock &ufoTimer)
	{
		if (this->state != NULL)
			this->state->Update(this->window,dt,timer,ufoTimer);
	}

	void Render()
	{
		if (this->state != NULL)
			this->state->Render(this->window);
	}

	~CurrentState()
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
		}
	}

private:
	RenderWindow* window;
	State *state;
};

extern CurrentState _currentState;
extern bool quitGame;