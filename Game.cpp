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

	//SDL_SetRenderDrawColor(gfx.GetRenderer(), 255, 255, 255, 255);
	//SDL_RenderClear(gfx.GetRenderer());
	while (running) {
		HandleInput();
		Update();
		Render();

		Clean();
	}

	Quit();



}

void Game::BindToScreenEdges() {
	if (player.GetPos()[1] < 0) {
		player.SetPosY(0);
		player.SetVelY(0);
	}
	if (player.GetPos()[0] < 0) {
		player.SetPosX(0);
		player.SetVelX(0);
	}	
	if (player.GetPos()[1] > gfx.screenHeight - player.dim[1]) {
		player.SetPosY(gfx.screenHeight - player.dim[1]);
		player.SetVelY(0);
	}
	if (player.GetPos()[0] > gfx.screenWidth - player.dim[0]) {
		player.SetPosX(gfx.screenWidth - player.dim[0]);
		player.SetVelX(0);
	}
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
							player.SetVel({ 0, - player.GetSpeed() });
						}
						break;
					}
					case SDLK_s:
					{
						if (velY <= 0 && posY < Graphics::screenHeight - player.dim[1]) {
							player.SetVel({ 0, player.GetSpeed() });
						}
						break;
					}
					case SDLK_a:
					{
						if (velX >= 0 && posX > 0) {
							player.SetVel({ - player.GetSpeed(), 0 });
						}
						break;
					}
					case SDLK_d:
					{
						if (velX <= 0 && posX <= Graphics::screenWidth - 1 - player.dim[0]) {
							player.SetVel({ player.GetSpeed(), 0 });
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
					//case SDLK_a:
					//{
					//	if (player.GetPos()[0] >= 1) {
					//		player.SetPos({ -1, 0 });
					//	}
					//	break;
					//}
					//case SDLK_d:
					//{
					//	if (player.GetPos()[0] < Graphics::screenWidth - 2) {
					//		player.SetPos({ 1, 0 });
					//	}
					//	break;
					//}
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
	BindToScreenEdges();
	player.SetPos({ player.GetPos()[0] + player.GetVel()[0], player.GetPos()[1] + player.GetVel()[1] });

}

void Game::Render()
{
	SDL_RenderClear(gfx.GetRenderer());

	if (config.game.showFps) {
		ShowFPS(0.1f);
	}

	std::vector<int> sprite_pos = { gfx.screenWidth / 2, gfx.screenHeight / 2 };
	gfx.DrawSprite("pokeball32.png", sprite_pos);
	
	std::vector<int> turtle_pos = { gfx.screenWidth - 200, gfx.screenHeight - 200 };
	gfx.DrawSprite("turtle32.png", turtle_pos);

	
	gfx.DrawSprite("turtle64.png", turtle2_pos);

	player.Draw(gfx);




	//switch render target back and render to the screen
	if (SDL_SetRenderTarget(gfx.GetRenderer(), NULL) == 0) {
		//SDL_RenderCopy(gfx.GetRenderer(), gfx.GetRenderingTexture(), NULL, NULL);
		SDL_RenderPresent(gfx.GetRenderer());
	}
	else {
		cout << "Error when switching render target back to the renderer: " << SDL_GetError() << endl;
	}
}


void Game::Clean()
{
}

void Game::ShowFPS(float seconds)
{
	CountFps();

	if (frameTimer > seconds) {
		float fra = float(frames) / frameTimer;
		ConvertFPS(fra);
		gfx.DrawFPSCounter(fps);

		frameTimer -= seconds;
		frames = 0;
	}
	else {
		frames += 1;
	}
}

void Game::CountFps()
{
	frameEnd = std::chrono::steady_clock::now();

	frameDur = frameEnd - frameStart;
	frameTimeSec = frameDur.count();

	frameStart = std::chrono::steady_clock::now();

	//just to make sure first run won't add (it's like 17000)
	if (frameTimeSec < 1) {
		frameTimer += frameTimeSec;
	}
}






bool Game::IsRunning()
{
	return running;
}

void Game::Quit() {
	gfx.Clean();
	running = false;
}

void Game::ConvertFPS(float framerate)
{
	sprintf_s(fps, "%.1f", framerate);
}


