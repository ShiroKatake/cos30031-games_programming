#include <iostream>
#include <string>

using namespace std;

enum class STATES {WELCOME, MENU, ABOUT, HELP, SELECT, HOF, PLAY_GAME, HI_SCORE, STOP};

bool running = true;
STATES state = STATES::WELCOME;

void welcome_update() {
	state = STATES::MENU;
}

void welcome_render() {
	cout << ">> Welcome State:" << endl;
}

void menu_update() {
	string command;
	cin >> command;
	if (command == "play") {
		state = STATES::PLAY_GAME;
	}
}

void menu_render() {
	cout << ">> Type 'play' to start: " << endl;
}

void play_game_update() {
	state = STATES::STOP;
}

void play_game_render() {
	cout << ">> You are playing the game! Done. " << endl;
}

int main() {
	while (running) {
		if (state == STATES::WELCOME) {
			welcome_render();
			welcome_update();
		}
		else if (state == STATES::MENU) {
			menu_render();
			menu_update();
		}
		else if (state == STATES::PLAY_GAME) {
			play_game_render();
			play_game_update();
		}
		else if (state == STATES::PLAY_GAME) {
			running = false;
		}
	}
	return 0;
}