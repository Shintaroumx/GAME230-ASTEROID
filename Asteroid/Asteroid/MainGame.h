#pragma once
#include"sfml.h"
#include <algorithm> 
#include"GameObject.h"
#include"Spaceship.h"
#include"Bullet.h"
#include"Asteroid.h"
#include"Item.h"
#include"UFO.h"
#include "GameState.h"
#include"Lives.h"
#include"Score.h"
#include "SoundManager.h"
#include"VisualEffect.h"


class MainGame :
	public State
{
public:
	void Start(RenderWindow* window);
	void Update(RenderWindow* window,float dt,Clock &timer, Clock &ufoTimer);
	void Render(RenderWindow* window);
	void Destroy(RenderWindow* window);
	
private:
	Vector2i getBucket(Vector2f pos);
	void bucket_add(Vector2i b, GameObject* obj);
	void bucket_remove(Vector2i b, GameObject* obj);
	void detect_collisions(GameObject* obj, Vector2i b);

	void Reset();

	//variable
	const float BUCKET_WIDTH = 100;
	const float BUCKET_HEIGHT = 100;
	const int COLUMNS = 14;
	const int ROWS = 9;
	std::vector<GameObject*> grid[14][9];

	bool isShotReady;
	bool ufoShot;
	bool shotTrigger;
	bool invincibleOn;
	bool shieldOn;
	bool bUFO;
	bool thrust;
	float interval;
	float ufoInterval;
	float shootingSpd;
	float t;
	int Anum;
	Lives* lives;
	Score* score;
	Font* font;
	Text* level;
	RectangleShape fire;
	SoundManager *SEManager;
	Texture* shipExplodeTexture;
	Texture* rockExplodeTexture;
	Texture tex;

	Spaceship *spaceShip = new Spaceship();
	std::vector<Bullet*> bullets;
	std::vector<GameObject*> objects;
	std::vector<VisualEffect*> effects;

};

extern int finalScore;