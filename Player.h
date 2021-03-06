#pragma once
#include <vector>
#include <SDL.h>
#include "Graphics.h"

class Player
{

public:
	Player() = default;
	Player(std::vector<int> in_pos);
	
	void SetPos(std::vector<int> new_pos);
	void SetPosX(int x);
	void SetPosY(int y);
	std::vector<int> GetSpaceshipFront();
	std::vector<int> GetPos();
	void SetVel(std::vector<float> new_vel);
	void SetVelX(float x);
	void SetVelY(float y);
	std::vector<float> GetVel();

	void Draw(Graphics& gfx);
	std::vector<int> dim = { 0, 0 };

	float GetSpeed();

private:
	SDL_Color color = {255, 0, 0, 255};
	SDL_Color color2 = {180, 200, 0, 255};
	std::vector<int> pos;
	std::vector<float> vel = { 0.0f, 0.0f };
	float speed = 3.0f;
	const char* spritePath = "spaceship_79x128.png";
};

