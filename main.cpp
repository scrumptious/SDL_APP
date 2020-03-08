#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

// init video and renderer
//void InitVideo() {
//	if (SDL_Init(SDL_INIT_VIDEO) != 0)
//	{
//		cout << "Video Initialization Error: " << SDL_GetError() << endl;
//	}
//	else
//	{
//		window = SDL_CreateWindow("Larkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
//		if (window == NULL)
//		{
//			cout << "Window Initialization Error: " << SDL_GetError() << endl;
//		}
//		else
//			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//			if (renderer == NULL)
//			{
//				cout << "Renderer Initialization Error: " << SDL_GetError() << endl;
//			} else
//			{
//				SDL_UpdateWindowSurface(window);
//			}
//	}
//}

//SDL_Texture* TexFromBmp(std::string imagePath)
//{
//	SDL_Surface* imageSrf = SDL_LoadBMP(imagePath.c_str());
//	SDL_Texture* tex = nullptr;
//	if (imageSrf == NULL)
//	{
//		cout << "Image Loading Failed: " << SDL_GetError() << endl;
//	}
//	else
//	{
//		tex = SDL_CreateTextureFromSurface(renderer, imageSrf);
//		SDL_FreeSurface(imageSrf);
//	}
//	return tex;
//}

int main(int argc, char* argv[]) {
	Game theGame = Game();

	while (theGame.IsRunning()) {
		theGame.Loop();

	}



	//SDL_Texture* tex1 = nullptr;
	//SDL_Event e;
	//SDL_Rect screenRect = { winWidth, winHeight, 0, 0 };
	//SDL_Rect texArea = { 0, 0, winWidth / 2, winHeight / 2 };
	//bool running = true;
	//std::vector<int> texLoc = { 0, 0 };
	//std::string imagePath = ("C:\\Users\\nerd\\Source\\Repos\\Project1\\x64\\Debug\\background.bmp");

	//InitVideo();
	//tex1 = TexFromBmp(imagePath);

	//while (running)
	//{
	//	if (SDL_PollEvent(&e)) {
	//		if (e.type == SDL_QUIT) {
	//			break;
	//		}
	//		if (e.type == SDL_KEYDOWN) {
	//			switch (e.key.keysym.sym) {
	//				case SDLK_q:
	//				{
	//					running = false;
	//					break;
	//				}
	//				case SDLK_w:
	//				{
	//					if (texLoc[1] >= 1) {
	//						texLoc[1] -= 1;
	//					}
	//					break;
	//				}
	//				case SDLK_s:
	//				{
	//					if (texLoc[1] < winHeight - 2) {
	//						texLoc[1] += 1;
	//					}
	//					break;
	//				}
	//				case SDLK_a:
	//				{
	//					if (texLoc[0] >= 1) {
	//						texLoc[0] -= 1;
	//					}
	//					break;
	//				}
	//				case SDLK_d:
	//				{
	//					if (texLoc[0] < winWidth - 2) {
	//						texLoc[0] += 1;
	//					}
	//					break;
	//				}
	//			}
	//		}
	//	}
	//	//First clear the renderer
	//	SDL_RenderClear(renderer);
	//	//Draw the texture
	//	SDL_Rect dstRect = { texLoc[0], texLoc[1], winWidth / 2, winHeight / 2 };
	//	SDL_RenderCopy(renderer, tex1, NULL, &dstRect);
	//	//Update the screen
	//	SDL_RenderPresent(renderer);

	//}

	return 0;
}