#pragma once
#include <vector>
#include <string>
class Bullet
{
public:
	Bullet();
	Bullet(std::vector<int> new_pos);
	Bullet(std::vector<int> new_pos, std::vector<int> new_vel);
	const char* spritePath = "bullet4.png";
	int getVelY();
	int getVelX();
	std::vector<int> pos;

private:
	std::vector<int> vel = {0, -5};
};