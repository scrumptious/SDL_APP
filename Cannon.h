#pragma once
#include <vector>
#include <string>
class Cannon
{
public:
	Cannon() = default;
	Cannon(std::vector<int> in_pos, int angle = 0);
	int GetAngle() const;
	std::vector<int> GetPos() const;
	int GetPosX() const;
	int GetPosY() const;
private:
	int angle = 0;
	std::vector<int> pos;
	std::string spritePath = "cannon32.png";
};

