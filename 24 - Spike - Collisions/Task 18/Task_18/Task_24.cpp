#include <string>
#include <iostream>
#include "SDL.h"
#include <cmath>

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
	rect.x = rand() % (800 - w);
	rect.y = rand() % (600 - h);
	rect.w = w;
	rect.h = h;

	return rect;
}

SDL_Rect InitializeRect(SDL_Rect &rect, int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;
}

//Doing a small reference to Unity's OnTriggerEnter2D (the logic seems to match)
bool IsBoxTriggerEnter2D(SDL_Rect &box1, SDL_Rect &box2) {
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

bool IsCircleTriggerEnter2D(SDL_Rect &circle1, SDL_Rect &circle2) {
	if (pow((circle1.x + circle1.w / 2) - (circle2.x + circle2.w / 2), 2) + pow((circle1.y + circle1.w / 2) - (circle2.y + circle2.w / 2), 2) > pow(circle1.w / 2 + circle2.w / 2, 2))
		return false;
	return true;
}

int main(int argg, char *argv[]) {
	const int fps = 60;
	int frameTime = 0;

	SDL_Window *window = nullptr;
	SDL_Texture *image2 = nullptr;
	SDL_Renderer *renderer = nullptr;

	SDL_Rect imageRect1;
	SDL_Rect imageRect2;
	SDL_Rect circleRect1;
	SDL_Rect circleRect2;
	SDL_Rect imagePos;

	SDL_Rect box1;
	SDL_Rect box2;

	SDL_Rect circleBox1;
	SDL_Rect circleBox2;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Task 16", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	image2 = LoadTexture("image2.bmp", renderer);

	SDL_QueryTexture(image2, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 3;
	frameHeight = textureHeight / 2;

	imageRect1.x = imageRect1.y = 0;
	imageRect1.w = frameWidth;
	imageRect1.h = frameHeight;

	imageRect2.x = imageRect2.y = 0;
	imageRect2.w = frameWidth;
	imageRect2.h = frameHeight;

	circleRect1.x = imageRect2.y = 0;
	circleRect1.w = frameWidth;
	circleRect1.h = frameHeight;

	circleRect2.x = imageRect2.y = 0;
	circleRect2.w = frameWidth;
	circleRect2.h = frameHeight;

	imageRect1.x = 0;
	imageRect2.x = frameWidth * 2;

	circleRect1.x = 0;
	circleRect1.y = frameWidth;

	circleRect2.x = frameWidth;
	circleRect2.y = frameWidth;

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				if (ev.key.keysym.sym == SDLK_1) {
					box1 = InitializeRect(imagePos, 300, 200, 200, 200);
					box2 = InitializeRect(imagePos, 100, 100);

					if (IsBoxTriggerEnter2D(box1, box2)) {
						cout << "box colliding" << endl;
					}

					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, image2, &imageRect1, &box1);
					SDL_RenderCopy(renderer, image2, &imageRect2, &box2);
					SDL_RenderPresent(renderer);
				}
				else if (ev.key.keysym.sym == SDLK_2) {
					circleBox1 = InitializeRect(imagePos, 300, 200, 200, 200);
					circleBox2 = InitializeRect(imagePos, 100, 100);

					if (IsCircleTriggerEnter2D(circleBox1, circleBox2)) {
						cout << "circle colliding" << endl;
					}

					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, image2, &circleRect1, &circleBox1);
					SDL_RenderCopy(renderer, image2, &circleRect2, &circleBox2);
					SDL_RenderPresent(renderer);
				}
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(image2);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	image2 = nullptr;
	renderer = nullptr;
	SDL_Quit();

	return 0;
}