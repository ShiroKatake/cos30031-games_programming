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

SDL_Rect InitializeRect(SDL_Rect &rect, int w, int h) {
	rect.x = rand() % (800 - 170);
	rect.y = rand() % (600 - 300);
	rect.w = w;
	rect.h = h;

	return rect;
}

bool IsTriggerEnter2D(SDL_Rect &box1, SDL_Rect &box2) {
	if (box1.y >= box2.y + box2.h)
		return false;
	if (box1.y + box1.h <= box2.y)
		return false;
	if (box1.x >= box2.x + box2.w)
		return false;
	if (box1.x + box1.w <= box2.x)
		return false;
	return true;
}

int main(int argg, char *argv[]) {
	const int fps = 60;
	int frameTime = 0;

	SDL_Window *window = nullptr;
	SDL_Texture *image1 = nullptr;
	SDL_Texture *image2 = nullptr;
	SDL_Renderer *renderer = nullptr;

	SDL_Rect imageRect1;
	SDL_Rect imageRect2;
	SDL_Rect imagePos;

	SDL_Rect box1;
	SDL_Rect box2;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Task 16", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	image1 = LoadTexture("image1.bmp", renderer);
	image2 = LoadTexture("image2.bmp", renderer);

	SDL_QueryTexture(image2, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 3;
	frameHeight = textureHeight;

	imageRect1.x = imageRect1.y = 0;
	imageRect1.w = frameWidth;
	imageRect1.h = frameHeight;

	imageRect2.x = imageRect2.y = 0;
	imageRect2.w = frameWidth;
	imageRect2.h = frameHeight;

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
				//Image 1 is red image
				imageRect1.x = 0;
				//Image 2 is blue image
				imageRect2.x = frameWidth * 2;

				box1 = InitializeRect(imagePos, 200, 200);
				box2 = InitializeRect(imagePos, 100, 100);

				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, image2, &imageRect1, &box1);
				SDL_RenderCopy(renderer, image2, &imageRect2, &box2);
				SDL_RenderPresent(renderer);

				if (IsTriggerEnter2D(box1, box2)) {
					cout << "colliding" << endl;
				}
				else {
					cout << "not colliding" << endl;
				}
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(image1);
	SDL_DestroyTexture(image2);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	image1 = nullptr;
	image2 = nullptr;
	renderer = nullptr;
	SDL_Quit();

	return 0;
}