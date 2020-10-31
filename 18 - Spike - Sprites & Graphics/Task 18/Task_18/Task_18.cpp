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

SDL_Rect *GetRandomRectPos(SDL_Rect &rect) {
	rect.x = rand() % (800 - 170);
	rect.y = rand() % (600 - 300);
	rect.w = 170;
	rect.h = 300;

	return &rect;
}

int main(int argg, char *argv[]) {
	const int fps = 60;
	int frameTime = 0;

	SDL_Window *window = nullptr;
	/*SDL_Texture *image1 = nullptr;*/
	SDL_Texture *image2 = nullptr;
	SDL_Renderer *renderer = nullptr;
	SDL_Rect imageRect;
	SDL_Rect imagePos;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Task 16", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	/*image1 = LoadTexture("image1.bmp", renderer);*/
	image2 = LoadTexture("image2.bmp", renderer);

	SDL_QueryTexture(image2, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 3;
	frameHeight = textureHeight;

	imageRect.x = imageRect.y = 0;
	imageRect.w = frameWidth;
	imageRect.h = frameHeight;
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	bool isRunning = true;
	SDL_Event ev;

	bool active0 = false;
	bool active1 = false;
	bool active2 = false;
	bool active3 = false;

	while (isRunning) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				if (ev.key.keysym.sym == 0) {
					SDL_RenderClear(renderer);
					SDL_RenderPresent(renderer);
				}
				else {
					switch (ev.key.keysym.sym)
					{
						case SDLK_0:
							break;

						case SDLK_1:
							imageRect.x = 0;
							active1 = !active1;
							active2 = false;
							active3 = false;
							cout << "active1: " << boolalpha << active1 << endl;
							cout << "active2: " << boolalpha << active2 << endl;
							cout << "active3: " << boolalpha << active3 << endl;
							break;

						case SDLK_2:
							imageRect.x = frameWidth;
							active1 = false;
							active2 = !active2;
							active3 = false;
							cout << "active1: " << boolalpha << active1 << endl;
							cout << "active2: " << boolalpha << active2 << endl;
							cout << "active3: " << boolalpha << active3 << endl;
							break;

						case SDLK_3:
							imageRect.x = frameWidth * 2;
							active1 = false;
							active2 = false;
							active3 = !active3;
							cout << "active1: " << boolalpha << active1 << endl;
							cout << "active2: " << boolalpha << active2 << endl;
							cout << "active3: " << boolalpha << active3 << endl;
							break;

						default:
							break;
					}
					SDL_RenderClear(renderer);
					if (active1 || active2 || active3) {
						SDL_RenderCopy(renderer, image2, &imageRect, GetRandomRectPos(imagePos));
					}
					SDL_RenderPresent(renderer);
				}				
			}
		}
	}

	SDL_DestroyWindow(window);
	//SDL_DestroyTexture(image1);
	SDL_DestroyTexture(image2);
	SDL_DestroyRenderer(renderer);
	
	window = nullptr;
	//image1 = nullptr;
	image2 = nullptr;
	renderer = nullptr;
	SDL_Quit();

	return 0;
}