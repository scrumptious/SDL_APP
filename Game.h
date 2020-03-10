#pragma once
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream> // to convert to or from const char*
#include <string>
#include "SDL.h"
#include "Player.h"
#include "Bullet.h"
#include "Config.h"
#include "Graphics.h"
#include "Utils.h"
#include "Color.h"


class Game
{
public:
	Game();
	~Game();
	//void Init();
	void Loop();
	bool IsRunning();


private:
	
	void HandleInput();
	void Update();
	void Render();

	void Clean();
	//fps methods
	void ShowFPS(float seconds);
	void CountFps();
	void ConvertFPS(float frameTimer);
	void CreateBullet();
	void BindToScreenEdges();
	void Quit();


public:
	std::vector<int> turtle2_pos = { gfx.screenWidth - 600, gfx.screenHeight - 400 };


private:
	bool running = true;
	const std::vector<int> initialPlayerPos = { gfx.screenWidth / 2, gfx.screenHeight / 2};

	SDL_Texture* turtle = NULL;

	Player player;
	Config config;
	Graphics gfx;
	Color* colors;
	std::vector<Bullet> bullets;


	float frameTimer = 0.0f;
	int frames = 0;
	char fps[10] = "";
	std::chrono::steady_clock::time_point frameStart;
	std::chrono::steady_clock::time_point frameEnd;
	std::chrono::duration<float> frameDur;
	float frameTimeSec = 0.0f;


};

