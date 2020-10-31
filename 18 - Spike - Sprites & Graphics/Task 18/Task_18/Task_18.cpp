#include <string>
#include <iostream>
#include "SDL.h"

using namespace std;

SDL_Texture *LoadTexture(string filepath, SDL_Renderer *renderer) {
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
	if (surface == NULL) {
		cout << "Error" << endl;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			cout << "Error" << endl;
		}
	}

	SDL_FreeSurface(surface);

	return texture;
}

int main(int argg, char *argv[]) {
	SDL_Window *window = nullptr;
	SDL_Texture *image1 = nullptr;
	SDL_Texture *image2 = nullptr;
	SDL_Rect *imageRect = nullptr;
	SDL_Renderer *renderer = nullptr;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Task 16", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	image1 = LoadTexture("image1.png", renderer);
	image2 = LoadTexture("image2.png", renderer);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	bool isRunning = true;
	SDL_Event ev;

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
						SDL_SetRenderDrawColor(renderer, rand() % 255 + 1,
							rand() % 255 + 1,
							rand() % 255 + 1,
							rand() % 255 + 1);
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