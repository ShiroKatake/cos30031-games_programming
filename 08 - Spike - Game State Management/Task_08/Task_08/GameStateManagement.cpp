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

class Menu : public State {
public:
	STATES update() override {
		string command;
		cin >> command;

		if (command == "play") {
			return STATES::PLAY_GAME;
		}
		else if (command == "hof") {
			return STATES::HOF;
		}
		else if (command == "about") {
			return STATES::ABOUT;
		}
		else if (command == "help") {
			return STATES::HELP;
		}
		else if (command == "select") {
			return STATES::SELECT;
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

	State* _current = &_welcome;
	STATES _state = STATES::WELCOME;
public:
	bool running() const { return _state != STATES::DONE; }

	void update() {
		_state = _current->update();

		if (_state == STATES::WELCOME) { _current = &_welcome; }
		else if (_state == STATES::MENU) { _current = &_menu; }
		else if (_state == STATES::HELP) { _current = &_help; }
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