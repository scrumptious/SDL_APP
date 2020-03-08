#include "Utils.h"
#include "SDL.h"
#include <stdio.h>


#include<string>
#include<iostream>

void checkError() {
	const char* error = SDL_GetError();
	if (*error) {
		SDL_Log("SDL error: %s", error);
		SDL_ClearError();
	}
}

