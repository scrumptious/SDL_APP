#pragma once
#include <vector>
#include <SDL.h>
#include "Graphics.h"

class Player
{

public:
	Player() = default;
	Player(std::vector<float> in_pos);
	
	void SetPos(std::vector<float> new_pos);
	std::vector<float> GetPos();
	void SetVel(std::vector<float> new_vel);
	std::vector<float> GetVel();

	void Draw(Graphics& gfx);
	const std::vector<int> dim = { 20, 20 };


private:
	SDL_Color color = {255, 0, 0, 255};
	std::vector<float> pos;
	std::vector<float> vel = { 0.0f, 0.0f };
};

