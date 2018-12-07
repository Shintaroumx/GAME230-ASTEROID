//#include"sfml.h"
//#include <algorithm> 
//#include<ctime>
//#include<cstdlib>
//#include"GameObject.h"
//#include"Spaceship.h"
//#include"Bullet.h"
//#include"Asteroid.h"
//
//using namespace sf;
//
////function
//void Start();
//void Update();
//void Render(RenderWindow &window);
//Vector2i getBucket(Vector2f pos);
//void bucket_add(Vector2i b, GameObject* obj);
//void bucket_remove(Vector2i b, GameObject* obj);
//void detect_collisions(GameObject* obj, Vector2i b);
//
////variable
//const float BUCKET_WIDTH = 100;
//const float BUCKET_HEIGHT = 100;
//const int COLUMNS = 14;
//const int ROWS = 9;
//std::vector<GameObject*> grid[COLUMNS][ROWS];
//
//bool isShotReady;
//float interval;
//float t;
//int hp=3;
//
//Spaceship *spaceShip=new Spaceship();
//std::vector<Bullet*> bullets;
//std::vector<GameObject*> objects;
//
//
///*int main()
//{
//	Start();
//	Update();
//
//	return 0;
//}*/
//
//
//void Start() {
//	isShotReady = true;
//	interval = 0;
//	objects.push_back(spaceShip);
//	for (int i = 0; i < 10; i++) {
//		Asteroid *a = new Asteroid(0);
//		objects.push_back(a);
//	}
//}
//
//
//void Update() {
//	sf::RenderWindow window(sf::VideoMode(1400, 900), "Asteroid");
//	Clock clock;
//	Clock timer;
//	float lifetime[50];
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		float dt = clock.restart().asSeconds();
//
//		//**Bullet interval
//		if (Keyboard::isKeyPressed(Keyboard::Space)&&isShotReady) {
//			Bullet *b = new Bullet();
//			bullets.push_back(b);
//			objects.push_back(b);
//			b->SetBullet(*spaceShip);
//			isShotReady = false;
//			timer.restart();
//		}
//		if (!isShotReady)
//			interval = timer.getElapsedTime().asSeconds();
//		if (interval >= 0.5) {
//			interval = timer.getElapsedTime().asSeconds() - 0.5;
//			isShotReady = true;
//		}
//
//
//		//**Check bullet lifetime
//		for (int i = 0; i < bullets.size();)
//		{
//			Bullet *b = bullets[i];
//			if(bullets[i]->isAlive)
//				lifetime[i]= bullets[i]->lifetime.getElapsedTime().asSeconds();
//			if (lifetime[i] > 1) {
//				bullets[i]->isAlive = false;
//				bullets.erase(bullets.begin() + i);
//				continue;
//			}
//			++i;
//		}
//
//
//		//**Collision
//		for (int i = 0; i < objects.size(); ++i)
//		{
//			GameObject * obj = objects[i];
//	/*		if (!obj->isAlive) {
//				objects.erase(objects.begin() + i);
//				continue;
//			}*/
//			Vector2i curBucket = getBucket(obj->getCenter());
//			obj->UpdateStatus(dt);
//			Vector2i newBucket = getBucket(obj->getCenter());
//			if (curBucket != newBucket)
//			{
//				bucket_remove(curBucket, obj);
//				bucket_add(newBucket, obj);
//			}
//			detect_collisions(obj, newBucket);
//			
//		}
//
//
//		for (auto i = objects.begin(); i != objects.end();)
//		{
//			GameObject *e = *i;
//
//			if (!e->isAlive)
//			{
//				i = objects.erase(i);
//				delete e;
//			}
//			else
//				i++;
//		}
//
//
//		//**Draw the objects
//		Render(window);
//	}
//}
//
//
//void Render(RenderWindow &window) {
//	window.clear();
//	//spaceShip.Draw(window);
//	for (int i = 0; i < objects.size(); ++i)
//	{
//		objects[i]->Draw(&window);
//	}
//	window.display();
//}
//
//
//Vector2i getBucket(Vector2f pos)
//{
//	int col = int(pos.x / BUCKET_WIDTH);
//	if (col < 0)
//		col = 0;
//	else if (col >= COLUMNS)
//		col = COLUMNS - 1;
//
//	int row = int(pos.y / BUCKET_HEIGHT);
//	if (row < 0)
//		row = 0;
//	else if (row >= ROWS)
//		row = ROWS - 1;
//
//	return Vector2i(col, row);
//}
//
//
//void bucket_add(Vector2i b,GameObject* obj)
//{
//	std::vector<GameObject*>& v = grid[b.x][b.y];
//	v.push_back(obj);
//}
//
//
//void bucket_remove(Vector2i b,GameObject* obj)
//{
//	std::vector<GameObject*>& v = grid[b.x][b.y];
//
//	for (int i = 0; i < v.size(); ++i)
//	{
//		if (v[i] == obj)
//		{
//			v.erase(v.begin() + i);
//			break;
//		}
//	}
//}
//
//
//void detect_collisions(GameObject* obj,Vector2i b)
//{
//	int left = std::max(b.x - 1, 0);
//	int right = std::min(b.x + 1, COLUMNS - 1);
//	int top = std::max(b.y - 1, 0);
//	int bot = std::min(b.y + 1, ROWS - 1);
//
//	for (int bx = left; bx <= right; ++bx)
//	{
//		for (int by = top; by <= bot; ++by)
//		{
//			std::vector<GameObject*> &v = grid[bx][by];
//			for (GameObject* o : v)
//			{
//				if (o != obj) {
//					if (obj->checkCollisionWith(o)) {
//						if (o->tag == "Spaceship") {
//							hp--;
//							if (hp <= 0) {
//								o->isAlive = false;
//								break;
//							}
//						}
//						if (o->tag == "Bullet") {
//							if (obj->isAlive) {
//								float angle = rand() % 360;
//								Asteroid *a = new Asteroid(obj->getCenter() + Vector2f(30, 30), angle, obj->GetLevel());
//								objects.push_back(a);
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}
