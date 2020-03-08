#pragma once
#include <SDL.h>
#include <iostream>
#include <assert.h>
#include "Config.h"

class Graphics
{
public:
	Graphics(const Config& cfg);
	~Graphics();

	void Init(const char* title, int x, int y, bool fullscreen);
	void ToScreen();
	void DrawRect(SDL_Rect& r, SDL_Color& c);
	void DrawTestRect();
	void DrawFPSCounter(char* frames);
	const void Clean();
	SDL_Renderer* GetRenderer();

private:
	//for private methods

public:
	static const int screenWidth = 800;
	static const int screenHeight = 600;

private:
	bool initialized = false;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

