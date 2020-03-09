#include "Player.h"

Player::Player(std::vector<float> in_pos)
{
	pos = in_pos;
}

void Player::SetPos(std::vector<float> new_pos)
{
	pos = new_pos;
}

void Player::SetPosX(float x)
{
	pos[0] = x;
}

void Player::SetPosY(float y)
{
	pos[1] = y;
}

std::vector<float> Player::GetPos()
{
	return pos;
}

void Player::SetVel(std::vector<float> new_vel)
{
	vel = new_vel;
}

void Player::SetVelX(float x)
{
	vel[0] = x;
}

void Player::SetVelY(float y)
{
	vel[1] = y;
}

std::vector<float> Player::GetVel()
{
	return vel;
}

void Player::Draw(Graphics& gfx)
{
	SDL_Rect r = { int(pos[0]), int(pos[1]), dim[0], dim[1] };
	std::vector<int> intPos = { int(pos[0]), int(pos[1]) };
	dim = gfx.DrawSpriteEx(spritePath, intPos);
}

float Player::GetSpeed()
{
	return speed;
}
