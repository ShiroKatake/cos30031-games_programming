//Code learned from lecture 2.2 COS30031 Games Programming by Clinton
#include <iostream>
#include <string>

using namespace std;

enum class STATES { WELCOME, MENU, ABOUT, HELP, SELECT, HOF, PLAY_GAME, HI_SCORE, STOP, DONE };

STATES _state = STATES::WELCOME;

class State {
public:
	virtual STATES update() = 0;
	virtual void render() = 0;
};

class Welcome : public State {
public:
	STATES update() override {
		return STATES::MENU;
	}
	void render() override {
		cout << ">> Welcome!" << endl;
	}
};

class StateManager {
private:
	Welcome _welcome;

	State* _current = &_welcome;
public:
	bool running() const { return _state != STATES::DONE; }

	void update() {
		if (_state == STATES::WELCOME) { _current = &_welcome; }

		_state = _current->update();
	}
	void render() { _current->render(); }
};


//A start on basic functionalities for the states
void welcome_update() {
	_state = STATES::MENU;
}

void welcome_render() {
	cout << ">> Welcome State:" << endl;
}

void menu_update() {
	string command;
	cin >> command;
	if (command == "play") {
		_state = STATES::PLAY_GAME;
	}
}

void menu_render() {
	cout << ">> Type 'play' to start: " << endl;
}

void play_game_update() {
	_state = STATES::STOP;
}

void play_game_render() {
	cout << ">> You are playing the game! Done. " << endl;
}




int main() {
	StateManager manager;

	while (manager.running()) {
		manager.render();
		manager.update();
	}
	return 0;
}