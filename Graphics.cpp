
#include "Graphics.h"
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
		window = SDL_CreateWindow(title, x, y, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN & fullscreen);
		if (window == NULL)
		{
			cout << "Window Initialization Error: " << SDL_GetError() << endl;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		}
		if (renderer == NULL) {
			cout << "Renderer Initialization Error: " << SDL_GetError() << endl;
		}
		initialized = true;
	}

}

void Graphics::ToScreen()
{
	SDL_RenderPresent(renderer);
}

void Graphics::DrawRect(SDL_Rect& r, SDL_Color& c)
{
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	//SDL_RenderClear(renderer);
	SDL_RenderDrawRect(renderer, &r);
}

void Graphics::DrawFPSCounter(char* ludwik)
{
	const char* fps = ludwik;
	if (TTF_Init() < 0) {
		std::cout << "Error Initialising TTF Fonts module: " << SDL_GetError() << std::endl;
	}
	TTF_Font* Courier = TTF_OpenFont("Courier.ttf", 72); //this opens a font style and sets a size
	SDL_Color White = {255,255,0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	std::cout << "frames: " << fps << std::endl;
	SDL_Color fg = { 0, 0, 0 };
	SDL_Color bg = { 0, 0, 0};

	SDL_Surface* surfaceMessage = TTF_RenderText_Shaded(Courier, fps, White, bg); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	SDL_Rect Message_rect = { 10, 10, 70, 30 }; //create a rect
	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance
	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	//Don't forget too free your surface and texture

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	TTF_CloseFont(Courier);
	TTF_Quit();
}

const void Graphics::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Renderer* Graphics::GetRenderer()
{
	return renderer;
}

//void Graphics::DrawTestRect()
//{
//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//	SDL_RenderClear(renderer);
//}