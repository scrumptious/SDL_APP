#include "Game.h"
using namespace std;


Game::Game()
	:
	player(initialPlayerPos),
	gfx(config)
{
	player.Draw(gfx);

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

void Game::CreateBullet()
{
	if(bullets.size() < 100) {
		bullets.push_back(Bullet(player.GetSpaceshipFront()));
	}
}

void Game::HandleInput()
{
	SDL_Event e;
	if (SDL_PollEvent(&e) != 0) {
		//handle keyboard input
		if (config.getActiveController() == config.controllers::KEYBOARD) {

			if (e.type == SDL_KEYDOWN) {
				int posX = player.GetPos()[0];
				int posY = player.GetPos()[1];
				float velX = player.GetVel()[0];
				float velY = player.GetVel()[1];

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
					case SDLK_SPACE:
					{
						//CreateBullet();
					}
					break;
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
					case SDLK_SPACE:
					{
						CreateBullet();
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
	BindToScreenEdges();
	player.SetPos({ player.GetPos()[0] + int(player.GetVel()[0]), player.GetPos()[1] + int(player.GetVel()[1]) });

	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].pos[1] > -20) {
			bullets[i].pos[1] += bullets[i].getVelY();
		}
	}
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

	//convert to const char* and print amount of bullets on the screen
	std::string nBullets;
	stringstream inputValue;
	inputValue << bullets.size();
	inputValue >> nBullets;
	nBullets = "bullets: " + nBullets;

	gfx.DisplayText(nBullets.c_str(), { 10, 10 }, 12, &(colors->black));
	//std::string playerPos = "player pos: " + to_string(player.GetPos()[0]) + ":" + to_string(player.GetPos()[1]);
	gfx.DisplayText(nBullets.c_str(), { 10, 10 }, 12, &(colors->black));
	gfx.DisplayText(
		( "player pos: " + to_string(player.GetPos()[0]) + ":" + to_string(player.GetPos()[1])
		).c_str(),
		{ 10, 35 }, 12, &(colors->black)
	);
	gfx.DisplayText(
		("player vel: " + to_string(player.GetVel()[0]) + ":" + to_string(player.GetVel()[1])
			).c_str(),
		{ 10, 60 }, 12, &(colors->black)
	);
	//std::vector<int> dot_pos = player.GetSpaceshipFront();
	//gfx.DrawSprite("pokeball4.png", dot_pos);
	//std::cout << "pokeball pos: " << dot_pos[0] << '/' << dot_pos[1] << endl;

	//std::cout << "bullet pos: " << bullet.pos[0] << '/' << bullet.pos[1] << endl;

	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].pos[1] > -10) {
   			gfx.DrawSprite(bullets[i].spritePath, bullets[i].pos);
		}
		else {
			bullets.erase(bullets.begin() + i);
		}
	}


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


