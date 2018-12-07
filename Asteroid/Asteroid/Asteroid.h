#ifndef _ASTEROID_HPP_
#define _ASTEROID_HPP_
#include "GameObject.h"
#include <math.h>
#include "sfml.h"


class Asteroid : 
	public GameObject
{
	static float speed[3];
	static float radius[3];

public:
	Asteroid(int level,float spd);
	Asteroid(sf::Vector2f position, float angle, int level,float spd);
	~Asteroid();

	virtual int GetLevel();
	void BreakDown();
	virtual bool checkCollisionWith(GameObject* obj);
	//virtual Vector2f getCenter();
	virtual void UpdateStatus(float dt);
	//virtual void Draw(RenderWindow &window);

private:
	Texture tex;
	Vector2f distance;
	int level;
	sf::Vector2f direction;
	
};
#endif
