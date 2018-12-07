#include "Bullet.h"


Bullet::Bullet()
{
	tag = "Bullet";
}

Bullet::~Bullet()
{
}


void Bullet::SetBullet(Spaceship &ship,Color clr,GameObject* obj)
{
	shape.setRadius(3);
	shape.setOrigin(3,3);
	shape.setFillColor(clr);
	shape.setPosition(obj->getCenter());
	if (clr == Color::White) {
		shape.setRotation(ship.rotation);
		forward.x = cos(ship.rotation * DEG2RAD);
		forward.y = sin(ship.rotation * DEG2RAD);
	}
	if (clr == Color::Red) {
		forward = ship.shape.getPosition() - obj->getCenter();
		forward.x /= 1000;
		forward.y /= 1000;
	}
}


void Bullet::UpdateStatus(float dt)
{
	if (!isAlive) return;

	Vector2f pos = shape.getPosition();
	pos.x += forward.x*dt*1000;
	pos.y += forward.y*dt*1000;
	shape.setPosition(pos);
}


//void Bullet::Draw(RenderWindow & window)
//{
//	window.draw(shape);
//}


//Vector2f Bullet::getCenter()
//{
//	return shape.getPosition();
//}





