#pragma once
#include <SDL.h>
#include <SDL_image.h>
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
	void DrawTexture(SDL_Texture* texture, std::vector<int> pos, int* w, int* h);
	void DrawRect(SDL_Rect& r, SDL_Color& strokeColor, SDL_Color& fillColor);
	void DrawSprite(const char* filepath, std::vector<int> pos);
	std::vector<int> DrawSpriteEx(const char* filepath, std::vector<int> pos);
	void DrawSpriteBMP(const char* filepath, std::vector<int> pos, SDL_Rect* srcRect = NULL);
	void ToScreen(const SDL_Color& c);
	void Clean();
	SDL_Texture* LoadTexture(const char* filepath);
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

