#include "Cannon.h"

Cannon::Cannon(std::vector<int> in_pos, int angle)
{
	pos = in_pos;
	angle = angle;
}

int Cannon::GetAngle() const
{
	return angle;
}

std::vector<int> Cannon::GetPos() const
{
	return { pos[0], pos[1] };
}

int Cannon::GetPosX() const
{
	return pos[0];
}

int Cannon::GetPosY() const
{
	return pos[1];
}

