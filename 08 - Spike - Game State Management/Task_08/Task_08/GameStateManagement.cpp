//Code learned from lecture 2.2 COS30031 Games Programming by Clinton
#include <iostream>
#include <string>

using namespace std;

enum class STATES { WELCOME, MENU, ABOUT, HELP, SELECT, HOF, PLAY_GAME, HI_SCORE, STOP, DONE };

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
		cout << ">> Welcome!\n" << endl;
	}
};

class Help : public State {
public:
	STATES update() override {
		return STATES::MENU;
	}
	void render() override {
		cout << ">> This is a help screen, have some help :D\n" << endl;
	}
};

class Select : public State {
public:
	STATES update() override {
		int command;
		cin >> command;

		if (command == 1) {
			return STATES::PLAY_GAME;
		}
		else {
			return STATES::SELECT;
		}
	}
	void render() override {
		cout << endl;
		cout << ">> Select a stage to play:" << endl;
		cout << ">> 1. The only stage that exists in the game but also the only stage with a lot of dramatic actions." << endl;
	}
};

class Hof : public State {
public:
	STATES update() override {
		return STATES::MENU;
	}
	void render() override {
		cout << ">> Welcome to the Hall of Fame of a game that doesn't exist yet . . .\n" << endl;
	}
};

class About : public State {
public:
	STATES update() override {
		return STATES::MENU;
	}
	void render() override {
		cout << ">> Author: Khang Trinh" << endl;
		cout << ">> Student ID: 102118468\n" << endl;
	}
};

class PlayGame : public State {
public:
	STATES update() override {
		return STATES::HI_SCORE;
	}
	void render() override {
		cout << ">> Game's starting . . ." << endl;
		cout << ">> *Insert dramatic boss fights here*" << endl;
	}
};

class Hi_Score : public State {
public:
	STATES update() override {
		string command;
		cin >> command;

		if (command != "") {
			return STATES::HOF;
		}
		else {
			return STATES::HI_SCORE;
		}
	}
	void render() override {
		cout << ">> Game's finished! Congratz you've achieved a new high score!" << endl;
		cout << ">> Please enter your name: ";
	}
};

class Menu : public State {
public:
	STATES update() override {
		string command;
		cin >> command;

		if (command == "help") {
			return STATES::HELP;
		}
		else if (command == "select") {
			return STATES::SELECT;
		}
		else if (command == "hof") {
			return STATES::HOF;
		}
		else if (command == "about") {
			return STATES::ABOUT;
		}
		return STATES::MENU;
	}
	void render() override {
		cout << ">> Type any of the following commands to proceed:" << endl;
		cout << ">> help: Instructions on how to play the game." << endl;
		cout << ">> select: Select a stage to play." << endl;
		cout << ">> hof: View the Hall of Fame." << endl;
		cout << ">> about: Details about the game." << endl;
	}
};

class StateManager {
private:
	Welcome _welcome;
	Menu _menu;
	Help _help;
	About _about;
	Select _select;
	PlayGame _playGame;
	Hi_Score _hiScore;
	Hof _hof;

	State* _current = &_welcome;
	STATES _state = STATES::WELCOME;
public:
	bool running() const { return _state != STATES::DONE; }

	void update() {
		//Unlike in the lecture, this has to be before the if's
		//because if not messages will be displayed twice
		_state = _current->update();

		if (_state == STATES::WELCOME) { _current = &_welcome; }
		else if (_state == STATES::MENU) { _current = &_menu; }
		else if (_state == STATES::HELP) { _current = &_help; }
		else if (_state == STATES::ABOUT) { _current = &_about; }
		else if (_state == STATES::SELECT) { _current = &_select; }
		else if (_state == STATES::PLAY_GAME) { _current = &_playGame; }
		else if (_state == STATES::HI_SCORE) { _current = &_hiScore; }
		else if (_state == STATES::HOF) { _current = &_hof; }
	}
	void render() { _current->render(); }
};

int main() {
	StateManager manager;

	while (manager.running()) {
		manager.render();
		manager.update();
	}
	return 0;
}