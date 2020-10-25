#include <string>
#include <iostream>
#include <SDL_mixer.h>
#include "SDL.h"

using namespace std;

int main(int argg, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_Window *window = SDL_CreateWindow("Task 16", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout << "Error: " << Mix_GetError() << endl;

	Mix_Music *bgm1 = Mix_LoadMUS("medieval.ogg");
	Mix_Music *bgm2 = Mix_LoadMUS("wind.mp3");
	Mix_Music *bgm3 = Mix_LoadMUS("accion.ogg");

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym)
				{
					case SDLK_0:
						if (Mix_PausedMusic())
							Mix_ResumeMusic();
						else
							Mix_PauseMusic();
						break;

					case SDLK_1:
						if (Mix_PlayingMusic()) {
							Mix_HaltMusic();
						}
						Mix_PlayMusic(bgm1, -1);
						break;

					case SDLK_2:
						if (Mix_PlayingMusic()) {
							Mix_HaltMusic();
						}
						Mix_PlayMusic(bgm2, -1);
						break;

					case SDLK_3:
						if (Mix_PlayingMusic()) {
							Mix_HaltMusic();
						}
						Mix_PlayMusic(bgm3, -1);
						break;

					default:
						break;
				}
			}
		}
		SDL_UpdateWindowSurface(window);
	}

	Mix_FreeMusic(bgm1);
	Mix_FreeMusic(bgm2);
	Mix_FreeMusic(bgm3);

	bgm1 = nullptr;
	bgm2 = nullptr;
	bgm3 = nullptr;
	window = nullptr;
	
	Mix_Quit();
	SDL_Quit();

	return 0;
}