#pragma once
#include <SDL.h>
#include <iostream>
#include <assert.h>
#include <vector>
#include "Config.h"

class Graphics
{
public:
	Graphics(const Config& cfg);
	~Graphics();

	void Init(const char* title, int x, int y, bool fullscreen);
	void DrawFPSCounter(const char* frames);
	void DrawRect(SDL_Rect& r, SDL_Color& strokeColor, SDL_Color& fillColor);
	void DrawSprite(const char* file, std::vector<int> pos, SDL_Rect* srcRect = NULL);
	void ToScreen(const SDL_Color& c);
	void Clean();
	SDL_Renderer* GetRenderer();
	SDL_Texture* GetRenderingTexture();

private:
	//for private methods

public:
	static const int screenWidth = 800;
	static const int screenHeight = 600;

private:
	SDL_Texture* renderingTexture;
	int lastFps = -1;
	bool initialized = false;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

