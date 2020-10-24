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
	SDL_StartTextInput();

	while (isRunning) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				//If r is pressed, get a random color and clear > display that color on the screen
				if (ev.key.keysym.sym == SDLK_r) {
					SDL_SetRenderDrawColor(renderer, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
					SDL_RenderClear(renderer);
					SDL_RenderPresent(renderer);
				}

				else if (ev.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
					text = text.substr(0, text.length() - 1);
			}
			else if (ev.type == SDL_TEXTINPUT)
				system("cls");
				text += ev.text.text;

			cout << text << endl;
			
		}
		SDL_UpdateWindowSurface(window);
	}
	SDL_StopTextInput();
	window = nullptr;
	SDL_Quit();
	return 0;
}