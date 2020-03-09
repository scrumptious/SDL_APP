#include "Graphics.h"
#include <sstream> // to convert to or from const char*
#include <iostream> // needs this one too
#include <vector>
#include "SDL_ttf.h"
#include "SDL_FontCache.h"

Graphics::Graphics(const Config& cfg)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL Initialization Error: " << SDL_GetError() << std::endl;

	}
	Init(cfg.game.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, cfg.video.fullscreen);
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(window);
}

void Graphics::Init(const char* title, int x, int y, bool fullscreen)
{
	using namespace std;
	assert(initialized == false);
	if (!initialized) {
		//initialize window and renderer
		window = SDL_CreateWindow(title, x, y, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN & fullscreen);
		if (window == NULL)
		{
			cout << "Window Initialization Error: " << SDL_GetError() << endl;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
		}
		if (renderer == NULL) {
			cout << "Renderer Initialization Error: " << SDL_GetError() << endl;
		}

		//let's render to this texture before rendering to the renderer
		renderingTexture = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, screenWidth, screenHeight
		);
		if (renderingTexture == NULL) {
			cout << "Error: Failed to create temporary rendering texture: " << SDL_GetError() << endl;
		}
		else {
			if (SDL_SetRenderTarget(renderer, renderingTexture) == -1) {
				cout << "Error: Failed to switch render target to rendering texture: " << SDL_GetError() << endl;
			}
			else {
				//background color
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "Error: Failed to initialize SDL_image: " << IMG_GetError() << endl;
				}
			}
		}
		initialized = true;
	}

}

void Graphics::DrawSpriteBMP(const char* filepath, std::vector<int> pos, SDL_Rect* srcRect)
{
	SDL_Surface* sprite_sur = SDL_LoadBMP(filepath);
	SDL_Texture* sprite_tex = SDL_CreateTextureFromSurface(renderer, sprite_sur);
	SDL_FreeSurface(sprite_sur);

	int sprW, sprH;
	SDL_QueryTexture(sprite_tex, NULL, NULL, &sprW, &sprH);
	SDL_Rect dstRect = { pos[0], pos[1], sprW, sprH };

	SDL_RenderCopy(renderer, sprite_tex, srcRect, &dstRect);
	SDL_DestroyTexture(sprite_tex);
}

void Graphics::ToScreen(const SDL_Color& c)
{
	SDL_RenderPresent(renderer);
}

void Graphics::DrawRect(SDL_Rect& rect, SDL_Color& strokeColor, SDL_Color& fillColor)
{
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);
	SDL_RenderDrawRect(renderer, &rect);
	//set color back to how it was
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Graphics::DrawSprite(const char* filepath, std::vector<int> pos)
{
	SDL_Texture* sprite_tex = LoadTexture(filepath);
	if (sprite_tex == NULL) {
		std::cout << "Error in DrawSprite(): " << SDL_GetError() << std::endl;
	}
	else {
		int w, h;
		DrawTexture(sprite_tex, pos, &w, &h);
	}
}

std::vector<int> Graphics::DrawSpriteEx(const char* filepath, std::vector<int> pos)
{
	std::vector<int> size = { 0, 0 };
	SDL_Texture* sprite_tex = LoadTexture(filepath);
	if (sprite_tex == NULL) {
		std::cout << "Error in DrawSprite(): " << SDL_GetError() << std::endl;
	}
	else {
		int w, h;
		DrawTexture(sprite_tex, pos, &w, &h);
		size[0] = w;
		size[1] = h;
	}
	return size;
}

void Graphics::DrawFPSCounter(const char* fps)
{
	SDL_Color green = { 0, 255, 0, 255 };
	SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);

	//convert to int
	int iFps = -1;
	std::stringstream strValue;
	strValue << fps;
	strValue >> iFps;

	//to don't check I added this line
	lastFps = iFps - 1;


	if (lastFps != iFps) {
		lastFps = iFps;

		if (TTF_Init() < 0) {
			std::cout << "Error Initialising TTF Fonts module: " << SDL_GetError() << std::endl;
		}
		TTF_Font* Courier = TTF_OpenFont("Courier.ttf", 72); //this opens a font style and sets a size
		TTF_Font* Roboto = TTF_OpenFont("Roboto-Regular.ttf", 24); //this opens a font style and sets a size
		SDL_Color fontColor;

		//color counter based on amount of fps
		if (iFps >= 50) {
			fontColor = { 0, 255, 0 };
		}
		else if (iFps < 50 && iFps >= 30) {
			fontColor = { 255, 255, 0 };
		}
		else if (iFps < 30) {
			fontColor = { 255, 0, 0 };
		}
		//figure out dimensions of RenderCopy rects
		int w = 0;
		int h = 0;
		SDL_Rect srcRect;
		SDL_Rect dstRect;
		//get text dimensions
		if (TTF_SizeText(Roboto, fps, &w, &h) != -1)
		{
			srcRect = { 0, 0, w, h };
			dstRect = { 5, 5, w, h };
		}
		else
		{
			srcRect = { 0, 0, 100, 80 };
			dstRect = { 5, 5, 100, 80 };
		}
		SDL_Rect dstRect2 = { 0, 0, w, h };
		std::cout << std::endl << "drawing fps counter" << std::endl;
		//SDL_Color bg = { 0, 0, 0, 255 };
		//render fps
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Roboto, fps, fontColor);
		//SDL_Surface* messageSurf = TTF_RenderText_Shaded(Roboto, fps, fontColor, bg);
		SDL_Texture* messageTex = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		//SDL_Texture* messageTex = SDL_CreateTextureFromSurface(renderer, messageSurf);
		SDL_RenderFillRect(renderer, &dstRect);
		SDL_RenderCopy(renderer, messageTex, NULL, &dstRect2);
		//SDL_RenderCopy(renderer, messageTex, &srcRect, &dstRect);

		//clean up
		SDL_FreeSurface(surfaceMessage);
		//SDL_FreeSurface(messageSurf);
		SDL_DestroyTexture(messageTex);
		TTF_CloseFont(Courier);
		TTF_CloseFont(Roboto);
		TTF_Quit();

	}

}

void Graphics::DrawTexture(SDL_Texture* texture, std::vector<int> pos, int* w, int* h)
{
	SDL_QueryTexture(texture, NULL, NULL, w, h);

	SDL_Rect spriteSrc = { 0, 0, *w, *h };
	SDL_Rect spriteDest = { pos[0], pos[1], *w, *h };

	SDL_RenderCopy(renderer, texture, &spriteSrc, &spriteDest);
	SDL_DestroyTexture(texture);
}

void Graphics::Clean()
{
	SDL_DestroyTexture(renderingTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Texture* Graphics::LoadTexture(const char* filepath)
{
	SDL_Texture* loadedTexture = NULL;

	SDL_Surface* tempSurface = IMG_Load(filepath);
	if (tempSurface == NULL) {
		std::cout << "Error Loading image! IMG_Load Error: " << SDL_GetError() << std::endl;
	}
	else {
		loadedTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (loadedTexture == NULL) {
			std::cout << "Error! Failed to create a texture from surface: " << SDL_GetError() << std::endl;
		}
		SDL_FreeSurface(tempSurface);
	}
	return loadedTexture;
}

SDL_Renderer* Graphics::GetRenderer()
{
	return renderer;
}

SDL_Texture* Graphics::GetRenderingTexture()
{
	return renderingTexture;
}

//void Graphics::DrawTestRect()
//{
//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//	SDL_RenderClear(renderer);
//} 