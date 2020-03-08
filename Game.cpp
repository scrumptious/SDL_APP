#include "Game.h"
using namespace std;


Game::Game()
	:
	player(initialPlayerPos),
	gfx(config)
{

}

Game::~Game()
{
}

void Game::Loop()
{
	while (running) {
		HandleInput();
		Update();
		Render();

		if (false
			//1 sec passed
			) {

			//CountFPS();
			//gfx.DrawFPSCounter(fps);
		}
	}

	Quit();



}



void Game::HandleInput()
{
	SDL_Event e;
	if (SDL_PollEvent(&e) != 0) {
		//handle keyboard input
		if (config.getActiveController() == config.controllers::KEYBOARD) {

			if (e.type == SDL_KEYDOWN) {
				float posX = player.GetPos()[0];
				float posY = player.GetPos()[1];
				float velX = player.GetVel()[0];
				float velY = player.GetVel()[1];
				printf("player pos: %f/%f \n", player.GetPos()[0], player.GetPos()[1]);
				printf("player vel: %f/%f \n", player.GetVel()[0], player.GetVel()[1]);

				switch (e.key.keysym.sym) {
					case SDLK_q:
						running = false;
						break;
					case SDLK_w:
					{
						if (velY >= 0 && posY > 0) {
							player.SetVel({ velX, -1.0f });
						}
						if (posY < 0) {
							player.SetPos({ posX, 0 });
						}

						break;
					}
					case SDLK_s:
					{
						if (velY <= 0 && posY < Graphics::screenHeight - 2) {
							player.SetVel({ velX, 1 });
						}
						if (posY >= Graphics::screenHeight) {
							player.SetPos( { posX, float(Graphics::screenHeight - 1 - player.dim[1]) } );
						}
						break;
					}
					case SDLK_a:
					{
						if (player.GetPos()[0] >= 1) {
							player.SetPos({ -1, 0 });
						}
						break;
					}
					case SDLK_d:
					{
						if (player.GetPos()[0] < Graphics::screenWidth - 2) {
							player.SetPos({ 1, 0 });
						}
						break;
					}
				}
			}
			else if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
					case SDLK_q:
						running = false;
						break;
					//case SDLK_w:
					//{
					//	if (player.GetPos()[1] >= 1) {
					//		player.SetPos({ 0, -1 });
					//	}
					//	break;
					//}
					//case SDLK_s:
					//{
					//	if (player.GetPos()[1] < Graphics::screenHeight - 2) {
					//		player.SetPos({ 0, 1 });
					//	}
					//	break;
					//}
					case SDLK_a:
					{
						if (player.GetPos()[0] >= 1) {
							player.SetPos({ -1, 0 });
						}
						break;
					}
					case SDLK_d:
					{
						if (player.GetPos()[0] < Graphics::screenWidth - 2) {
							player.SetPos({ 1, 0 });
						}
						break;
					}
				}
			}
		}//end of keyboard input handling

		//handle mouse input
		if (config.getActiveController() == config.controllers::MOUSE) {
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					break;

				case SDL_BUTTON_RIGHT:
					break;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					break;

				case SDL_BUTTON_RIGHT:
					break;
				}
			}
		}
	}
}

void Game::Update()
{
	//player.SetPos({ player.GetPos()[0] + player.GetVel()[0], player.GetPos()[1] + player.GetVel()[1] });

}

void Game::Render()
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	player.Draw(gfx);
	gfx.ToScreen();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::chrono::duration<float> runtime = end - start;
	float durationSeconds = runtime.count();

	frameTimer += durationSeconds;
	frames += 1;
	if (frameTimer > 1) {
		int fra = int(frames / frameTimer);
		CountFPS(fra);
		//const char* fpsToShow = "62 ";
		gfx.DrawFPSCounter(fps);

		frameTimer -= 1;
		frames = 0;
	}

	//SDL_Surface* background = SDL_LoadBMP("background.bmp");
	//SDL_Surface* sprite = SDL_LoadBMP("dog.bmp");

	//SDL_Texture* tex_bg = SDL_CreateTextureFromSurface(renderer, background);
	//SDL_FreeSurface(background);

	//SDL_Texture* tex_spr = SDL_CreateTextureFromSurface(renderer, sprite);
	//SDL_FreeSurface(sprite);

	//for (int i = 0; i < 3; ++i) {
	//	//First clear the renderer
	//	SDL_RenderClear(renderer);
	//	//Draw the texture
	//	SDL_RenderCopy(renderer, tex_spr, NULL, NULL);
	//	//Update the screen
	//	SDL_RenderPresent(renderer);
	//	//Take a quick break after all that hard work
	//	SDL_Delay(1000);
	//}


	//SDL_Delay(3000);
	//SDL_RenderPresent(renderer);

}




bool Game::IsRunning()
{
	return running;
}

void Game::Quit() {
	gfx.Clean();
	running = false;
}

void Game::CountFPS(int framerate)
{
	sprintf_s(fps, "%d", framerate);
}


