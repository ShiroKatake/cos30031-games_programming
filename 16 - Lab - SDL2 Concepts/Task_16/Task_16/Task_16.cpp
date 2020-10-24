#include <string>
#include <iostream>
#include "SDL.h"
using namespace std;
//Code learned from https://www.youtube.com/watch?v=QQzAHcojEKg&ab_channel=Let%27sMakeGames

int main(int argg, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	bool isRunning = true;
	SDL_Event ev;

	string text = "";

	while (isRunning) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym)
				{
					//If r is pressed, get a random color and clear > display that color on the screen
					case SDLK_r:
					{
						SDL_SetRenderDrawColor(renderer, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
						SDL_RenderClear(renderer);
						SDL_RenderPresent(renderer);
						break;
					}

					//If q is pressed, exit
					case SDLK_q:
						isRunning = false;
						break;

					default:
						break;
				}
			}			
		}
		SDL_UpdateWindowSurface(window);
	}

	window = nullptr;
	SDL_Quit();

	return 0;
}