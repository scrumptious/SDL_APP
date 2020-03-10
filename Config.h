#pragma once
#include <SDL.h>

class Config
{
public:
	enum controllers
	{
		NONE,
		KEYBOARD,
		MOUSE,
		GAMEPAD,
		CONTROLLERS_TOTAL
	};
	int getActiveController();
	void setActiveController(int c);

	struct {
		const char* title = "Ludanoid";
		bool showFps = 0;
	} game;

	struct {
		bool fullscreen = false;
		SDL_Color bgColor = { 255, 255, 255, 255 };
	} video;
private:
	int activeController = controllers::KEYBOARD;

};

