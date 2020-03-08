#pragma once
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include "SDL.h"
#include "Player.h"
#include "Config.h"
#include "Graphics.h"
#include "Utils.h"


class Game
{
public:
	Game();
	~Game();
	//void Init();
	void HandleInput();
	void Update();
	void Render();
	void Loop();
	bool IsRunning();
	void Quit();

private:
	void CountFPS(int frameTimer);



private:
	bool running = true;
	const std::vector<float> initialPlayerPos = { 100.0f, 100.0f };

	Player player;
	Config config;
	Graphics gfx;

	float frameTimer = 0.0f;
	int frames = 0;
	char fps[10];
	std::chrono::steady_clock::time_point now;

};

