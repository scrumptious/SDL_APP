#include "Player.h"

Player::Player(std::vector<float> in_pos)
{
	pos = in_pos;
}

void Player::SetPos(std::vector<float> new_pos)
{
	pos = new_pos;
}

std::vector<float> Player::GetPos()
{
	return pos;
}

void Player::SetVel(std::vector<float> new_vel)
{
	vel = new_vel;
}

std::vector<float> Player::GetVel()
{
	return vel;
}

void Player::Draw(Graphics& gfx)
{
	SDL_Rect r = { int(pos[0]), int(pos[1]), dim[0], dim[1] };
	gfx.DrawRect(r, color, color2);
}
