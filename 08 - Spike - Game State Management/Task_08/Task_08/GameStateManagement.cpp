//Code learned from lecture 2.2 COS30031 Games Programming by Clinton
#include <iostream>
#include <string>

using namespace std;

enum class STATES { WELCOME, MENU, ABOUT, HELP, SELECT, HOF, PLAY_GAME, HI_SCORE, STOP, QUIT };

class State {
public:
	virtual STATES update() = 0;
	virtual void render() = 0;
};

class About : public State {
public:
	STATES update() override {
		cin.ignore();
		cin.get();
		return STATES::MENU;
	}
	void render() override {
		cout << endl;
		cout << "Zorkish :: About" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "Written by: Khang Trinh - 102118468" << endl;
		cout << "Press Enter to return to the Main Menu" << endl;
	}
};

class Help : public State {
public:
	STATES update() override {
		cin.ignore();
		cin.get();
		return STATES::MENU;
	}
	void render() override {
		cout << endl;
		cout << "Zorkish :: Help" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "The following commands are supported:" << endl;
		cout << "quit," << endl;
		cout << "hiscore (for testing)" << endl;
		cout << "Press Enter to return to the Main Menu" << endl;
	}
};

class Select : public State {
public:
	STATES update() override {
		int command;
		cin >> command;

		if (command > 0 && command < 4) {
			return STATES::PLAY_GAME;
		}
		else {
			return STATES::SELECT;
		}
	}
	void render() override {
		cout << endl;
		cout << "Zorkish :: Select Adventure" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "Choose your adventure:" << endl;
		cout << "1. Mountain World" << endl;
		cout << "2. Water World" << endl;
		cout << "3. Box World" << endl;
		cout << "Select 1-3:> ";
	}
};

class Hof : public State {
public:
	STATES update() override {
		cin.ignore();
		cin.get();
		return STATES::MENU;
	}
	void render() override {
		cout << endl;
		cout << "Zorkish :: Hall of Fame" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "Top 10 Zorkish Adventure Champions" << endl;
		cout << "Press Enter to return to the Main Menu" << endl;
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
		cout << endl;
		cout << "Zorkish :: New High Score" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "Congratulations!" << endl;
		cout << "You have made it to the Zorkish Hall Of Fame" << endl;
		cout << "Adventure: The adventure that the player went chose . . ." << endl;
		cout << "Score: The score that made to the Hall of Fame ;)" << endl;
		cout << "Please type your name so that it will not be saved and press enter: " << endl;
		cout << ":> ";
	}
};

class PlayGame : public State {
public:
	STATES update() override {
		string command;
		cin >> command;

		if (command == "quit") {
			return STATES::MENU;
		}
		else if (command == "hiscore") {
			return STATES::HI_SCORE;
		}
		else {
			return STATES::PLAY_GAME;
		}
	}
	void render() override {
		cout << endl;
		cout << "Welcome to Zorkish: Void World" << endl;
		cout << "This world is simple and pointless. Used it to test Zorkish phase 1 spec." << endl;
		cout << ":> ";
	}
};

class Menu : public State {
public:
	STATES update() override {
		int command;
		cin >> command;

		switch (command)
		{
			case 1:
				return STATES::SELECT;
				break;
			case 2:
				return STATES::HOF;
				break;
			case 3:
				return STATES::HELP;
				break;
			case 4:
				return STATES::ABOUT;
				break;
			case 5:
				return STATES::QUIT;
				break;
			default:
				return STATES::MENU;
				break;
		}
	}
	void render() override {
		cout << endl;
		cout << "Zorkish :: Main Menu" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "\nWelcome to Zorkish Adventures\n" << endl;
		cout << "1. Select Adventure and Play" << endl;
		cout << "2. Hall Of Fame" << endl;
		cout << "3. Help" << endl;
		cout << "4. About" << endl;
		cout << "5. Quit" << endl;
		cout << "Select 1-5:> ";
	}
};

class StateManager {
private:
	//Declare all of your states here
	Menu _menu;
	Help _help;
	About _about;
	Select _select;
	PlayGame _playGame;
	Hi_Score _hiScore;
	Hof _hof;

	State* _current = &_menu;
	STATES _state = STATES::WELCOME;
public:
	//Check if the application is still running
	bool running() const { return _state != STATES::QUIT; }

	//Calling update here would call update() for the respective state
	void update() {
		//Unlike in the lecture, this has to be before the if's
		//because if not messages will be displayed twice
		_state = _current->update();

		//Change the game to this state if the state changes
		if (_state == STATES::MENU) { _current = &_menu; }
		else if (_state == STATES::HELP) { _current = &_help; }
		else if (_state == STATES::ABOUT) { _current = &_about; }
		else if (_state == STATES::SELECT) { _current = &_select; }
		else if (_state == STATES::PLAY_GAME) { _current = &_playGame; }
		else if (_state == STATES::HI_SCORE) { _current = &_hiScore; }
		else if (_state == STATES::HOF) { _current = &_hof; }
	}

	//Calling render here would call render() for the respective state
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