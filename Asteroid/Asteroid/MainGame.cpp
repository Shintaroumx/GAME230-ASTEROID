#include"MainGame.h"
#include "Menu.h"
#include "GameOver.h"
#include"Win.h"
#include <iostream>

using namespace sf;

void MainGame::Start(RenderWindow* window) {
	SEManager = new SoundManager;
	SEManager->InitializeSoundEffect();

	shipExplodeTexture = new Texture;
	rockExplodeTexture = new Texture;
	shipExplodeTexture->loadFromFile("type_B.png");
	rockExplodeTexture->loadFromFile("type_C.png");
	tex.loadFromFile("fire.png");

	this->font = new Font();
	this->font->loadFromFile("visitor1.ttf");

	this->score = new Score(*font, 48U);

	this->lives = new Lives(*font, 48U);
	this->lives->setFillColor(Color::White);
	this->lives->setPosition(window->getSize().x - this->lives->getGlobalBounds().width, 0);

	this->level = new Text("Level: " + std::to_string(levelIndex), *font, 32U);
	this->level->setFillColor(Color::White);
	this->level->setPosition((window->getSize().x - this->lives->getGlobalBounds().width) / 2, 32);

	fire.setSize(Vector2f(40, 20));
	fire.setOrigin(20, 10);
	fire.setTexture(&tex);

	thrust = false;
	Anum = 0;
	shootingSpd = 0.5f;
	invincibleOn = false;
	shieldOn = false;
	isShotReady = true;
	ufoShot = true;
	shotTrigger = true;
	bUFO = false;
	interval = 0;
	ufoInterval = 0;
	objects.push_back(spaceShip);
	for (int i = 0; i < levelIndex; i++) {
		Asteroid *a = new Asteroid(0,levelIndex);
		objects.push_back(a);
		Anum += 7;
	}

}


void  MainGame::Update(RenderWindow* window,float dt,Clock &timer,Clock &ufoTimer) {
	
	lives->Update();
	score->Update();

	fire.setPosition(Vector2f(spaceShip->getCenter().x- cos(spaceShip->rotation * DEG2RAD) * 50, spaceShip->getCenter().y - sin(spaceShip->rotation * DEG2RAD) * 50));
	fire.setRotation(spaceShip->rotation);

	if (live <= 0)
	{
		finalScore = score->value;
		_currentState.SetState(new GameOver);
	}

	if (Anum == 0)
	{
		levelIndex += 1;
		
		_currentState.SetState(new Win());
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		_currentState.SetState(new Menu);


	float lifetime[50];
	float lifetime2[50];

		//**Bullet interval
		if (Keyboard::isKeyPressed(Keyboard::Space) && isShotReady && SEManager->CheckPlayStatus(LaserSound) == true) {
			SEManager->PlaySoundEffect(LaserSound);
			Bullet *b = new Bullet();
			bullets.push_back(b);
			objects.push_back(b);
			b->SetBullet(*spaceShip,Color::White, spaceShip);
			isShotReady = false;
			timer.restart();
		}
		if (!isShotReady)
			interval = timer.getElapsedTime().asSeconds();
		if (interval >= shootingSpd) {
			interval = timer.getElapsedTime().asSeconds() - shootingSpd;
			isShotReady = true;
		}


		if (bUFO&&ufoShot) {
			Bullet *b = new Bullet();
			bullets.push_back(b);
			objects.push_back(b);
			for (int i = 0; i < objects.size(); ++i)
			{
				if (objects[i]->tag == "UFO") {
					GameObject* ufo = objects[i];
					b->SetBullet(*spaceShip, Color::Red, ufo);
				}
			}
			ufoShot = false;
			ufoTimer.restart();
		}
		if (!ufoShot)
			ufoInterval = ufoTimer.getElapsedTime().asSeconds();
		if (ufoInterval >= 1) {
			ufoInterval = ufoTimer.getElapsedTime().asSeconds() - 1;
			ufoShot = true;
		}


		if (Keyboard::isKeyPressed(Keyboard::Up) && spaceShip->isAlive&&SEManager->soundThrust->getStatus() != SoundSource::Playing) {
			SEManager->PlaySoundEffect(ThrustSound);
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
			thrust = true;
		else thrust = false;


		//**Check bullet lifetime
		for (int i = 0; i < bullets.size();)
		{
			if (bullets[i]->isAlive)
				lifetime[i] = bullets[i]->lifetime.getElapsedTime().asSeconds();
			if (lifetime[i] > 1) {
				bullets[i]->isAlive = false;
				bullets.erase(bullets.begin() + i);
				continue;
			}
			++i;
		}


		//**Check Effect lifetime
		for (int i = 0; i < effects.size();++i)
		{
			if (effects[i]->isAlive)
				lifetime2[i] = effects[i]->lifetime.getElapsedTime().asSeconds();
			if (lifetime2[i] > 0.2) {
				effects[i]->isAlive = false;
			}
		}



		//**Collision
		for (int i = 0; i < objects.size(); ++i)
		{
			GameObject * obj = objects[i];
			Vector2i curBucket = getBucket(obj->getCenter());
			obj->UpdateStatus(dt);
			Vector2i newBucket = getBucket(obj->getCenter());
			if (curBucket != newBucket)
			{
				bucket_remove(curBucket, obj);
				bucket_add(newBucket, obj);
			}
			detect_collisions(obj, newBucket);

		}


		for (auto i = objects.begin(); i != objects.end();)
		{
			GameObject *e = *i;

			if (!e->isAlive)
			{
				i = objects.erase(i);
				delete e;
			}
			else
				i++;
		}

	
		for (auto i = effects.begin(); i != effects.end();)
		{
			GameObject *e = *i;

			if (!e->isAlive)
			{
				i = effects	.erase(i);
				delete e;
			}
			else
				i++;
		}

}



void  MainGame::Render(RenderWindow* window) {
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Draw(window);
	for (int i = 0; i < effects.size(); ++i)
		effects[i]->Draw(window);
	if(thrust)
		window->draw(fire);
	window->draw(*score);
	window->draw(*lives);
	window->draw(*level);
}



void MainGame::Destroy(RenderWindow* window)
{
	delete this->score;
	delete this->lives;
	delete this->font;
	delete this->level;
	delete this->rockExplodeTexture;
	delete this->shipExplodeTexture;
}



Vector2i  MainGame::getBucket(Vector2f pos)
{
	int col = int(pos.x / BUCKET_WIDTH);
	if (col < 0)
		col = 0;
	else if (col >= COLUMNS)
		col = COLUMNS - 1;

	int row = int(pos.y / BUCKET_HEIGHT);
	if (row < 0)
		row = 0;
	else if (row >= ROWS)
		row = ROWS - 1;

	return Vector2i(col, row);
}


void  MainGame::bucket_add(Vector2i b, GameObject* obj)
{
	std::vector<GameObject*>& v = grid[b.x][b.y];
	v.push_back(obj);
}


void  MainGame::bucket_remove(Vector2i b, GameObject* obj)
{
	std::vector<GameObject*>& v = grid[b.x][b.y];

	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] == obj)
		{
			v.erase(v.begin() + i);
			break;
		}
	}
}


void  MainGame::detect_collisions(GameObject* obj, Vector2i b)
{
	int left = std::max(b.x - 1, 0);
	int right = std::min(b.x + 1, COLUMNS - 1);
	int top = std::max(b.y - 1, 0);
	int bot = std::min(b.y + 1, ROWS - 1);

	for (int bx = left; bx <= right; ++bx)
	{
		for (int by = top; by <= bot; ++by)
		{
			std::vector<GameObject*> &v = grid[bx][by];
			for (GameObject* o : v)
			{
				if (o != obj) {
					if (obj->checkCollisionWith(o)) 
					{
						if (obj->tag == "Asteroid"&&o->tag == "Spaceship"&&!invincibleOn) {
							SEManager->PlaySoundEffect(DestroySound);
							VisualEffect *explosionEffect_ship = new VisualEffect(ShipExplode, shipExplodeTexture, rockExplodeTexture,o);
							effects.push_back(explosionEffect_ship);

							if(!shieldOn)
							    lives->RemoveLife();
							o->shape.setPosition(Vector2f(700, 450));
							o->shape.setFillColor(Color::White);
							Reset();
						}
						if (obj->tag == "Asteroid"&&o->tag == "Bullet"&&o->isAlive&&o->shape.getFillColor()==Color::White) 
						{
							if (obj->isAlive) {
								float angle = rand() % 360;
								Asteroid *a = new Asteroid(obj->getCenter() + Vector2f(30, 30), angle, obj->GetLevel(),levelIndex);
								objects.push_back(a);
							}
							score->AddScore();
							Anum -= 1;
							SEManager->PlaySoundEffect(DestroySound);
							VisualEffect *explosionEffect_ship = new VisualEffect(RockExplode, shipExplodeTexture, rockExplodeTexture, obj);
							effects.push_back(explosionEffect_ship);


							o->isAlive = false;

							if (Anum % 3 == 1) {
								Item *item = new Item(obj, Color::Red);
								objects.push_back(item);
							}
							if (Anum % 4 == 1) {
								Item *item = new Item(obj, Color::Green);
								objects.push_back(item);
							}
							if (Anum % 5 == 1) {
								UFO *ufo = new UFO(obj);
								objects.push_back(ufo);
								bUFO = true;
							}
							if (Anum % 7 == 1) {
								Item *item = new Item(obj, Color::White);
								objects.push_back(item);
							}
								
						}


						if (obj->tag == "Shield"&&o->tag == "Spaceship") {
							if (!invincibleOn) {
								shieldOn = true;
								SEManager->PlaySoundEffect(PowerUp);
								o->shape.setFillColor(Color::Green);
							}
							obj->isAlive = false;
						}
						if (obj->tag == "RapidShoot"&&o->tag == "Spaceship") {
							shootingSpd = 0.1f;
							SEManager->PlaySoundEffect(PowerUp);
							obj->isAlive = false;
						}
						if (obj->tag == "Invincible"&&o->tag == "Spaceship") {
							obj->isAlive = false;
							SEManager->PlaySoundEffect(PowerUp);
							invincibleOn = true;
							o->shape.setFillColor(Color::Blue);
						}
						if (invincibleOn&&Anum % 6 == 5) {
							invincibleOn = false;
							if ( !shieldOn) {
								o->shape.setFillColor(Color::White);
							}
							if (shieldOn) {
								o->shape.setFillColor(Color::Green);
							}
						}
						if (shootingSpd==0.1f&&Anum%9==1)
							shootingSpd = 0.5f;


						if (obj->tag == "UFO"&&o->tag == "Spaceship" && !invincibleOn) {
							SEManager->PlaySoundEffect(DestroySound);
							VisualEffect *explosionEffect_ship = new VisualEffect(ShipExplode, shipExplodeTexture, rockExplodeTexture, o);
							effects.push_back(explosionEffect_ship);


							if(!shieldOn)
							    lives->RemoveLife();
							o->shape.setPosition(Vector2f(700, 450));
							obj->isAlive = false;
							bUFO = false;
						}
						if (obj->tag == "Spaceship"&&o->tag == "Bullet" && !invincibleOn && o->shape.getFillColor() == Color::Red) {
							o->isAlive = false;
							SEManager->PlaySoundEffect(DestroySound);
							VisualEffect *explosionEffect_ship = new VisualEffect(ShipExplode, shipExplodeTexture, rockExplodeTexture, obj);
							effects.push_back(explosionEffect_ship);

							if(!shieldOn)
							   lives->RemoveLife();
							obj->shape.setPosition(Vector2f(700, 450));
							Reset();
							o->shape.setFillColor(Color::White);
						}

						if (obj->tag == "UFO"&&o->tag == "Bullet"&&o->shape.getFillColor()==Color::White) {
							obj->isAlive = false;
							o->isAlive = false;
							bUFO = false;
							score->AddScore();
							SEManager->PlaySoundEffect(DestroySound);
						}
					}
				}
			}
		}
	}
}


void  MainGame::Reset() {
	shootingSpd = 0.5f;
	invincibleOn = false;
	shieldOn = false;
}