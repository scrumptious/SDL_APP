#pragma once
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
	} game;

	struct {
		bool fullscreen = false;
	} video;
private:
	int activeController = controllers::KEYBOARD;

};
