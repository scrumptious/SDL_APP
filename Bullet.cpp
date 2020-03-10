#include "Bullet.h"

Bullet::Bullet()
{
	pos = { 0, 0 };
}

Bullet::Bullet(std::vector<int> new_pos)
{
	pos = new_pos;
}

Bullet::Bullet(std::vector<int> new_pos, std::vector<int> new_vel)
{
	pos = new_pos;
	vel = new_vel;
}

int Bullet::getVelX()
{
	return vel[0];
}

int Bullet::getVelY()
{
	return vel[1];
}
