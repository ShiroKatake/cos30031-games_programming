//Code learned from lecture 2.2 COS30031 Games Programming by Clinton
#include <iostream>
#include <string>

using namespace std;

enum class STATES { WELCOME, MENU, ABOUT, HELP, SELECT, HOF, PLAY_GAME, HI_SCORE, STOP, DONE };

bool running = true;
STATES state = STATES::WELCOME;

class State {
public:
	virtual void update() = 0;
	virtual void render() = 0;
};

class Welcome : public State {
public:
	void update() override {
		state = STATES::MENU;
	}
	void render() override {
		cout << ">> Welcome!" << endl;
	}
};

class StateManager {
private:
	Welcome _welcome;

	State* _current = &_welcome;
	bool _running = true;
public:
	bool running() const { return state != STATES::DONE; }

	State* current() {
		if (state == STATES::WELCOME) { _current = &_welcome; }

		return _current;
	}
};


//A start on basic functionalities for the states
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
	StateManager manager;

	while (manager.running()) {
		manager.current()->render();
		manager.current()->update();
	}
	return 0;
}