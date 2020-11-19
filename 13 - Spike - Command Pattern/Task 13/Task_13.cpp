#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

class CommandHandler;

class Command {
public:
	string alias;
	CommandHandler* commandHandler;

	Command(string alias, CommandHandler* commandHandler);
	virtual void execute(vector<string> input) = 0;
	void ChangeAlias(string alias) {
		this->alias = alias;
	}
};

class CommandHandler {
private:

public:
	vector<Command*> commands;
	void AddCommand(Command* command) {
		commands.push_back(command);
	}

	void HandleCommand(string input) {
		istringstream buf(input);
		istream_iterator<string> beg(buf), end;

		vector<string> args(beg, end);

		for (Command* command : commands) {
			if (command->alias == args[0])
				command->execute(args);
		}
	}
};

Command::Command(string alias, CommandHandler* commandHandler) {
	this->alias = alias;
	this->commandHandler = commandHandler;
	this->commandHandler->AddCommand(this);
}

class Go : public Command {
public:
	Go(string alias, CommandHandler* commandHandler) : Command(alias, commandHandler) {
	}

	void execute(vector<string> arg) override {
		cout << alias << " command received. Parameter: " << arg[1] << endl;
	}
};

class Help : public Command {
public:
	Help(string alias, CommandHandler* commandHandler) : Command(alias, commandHandler) {
	}

	void execute(vector<string> arg) override {
		cout << alias << " command received. Here are the available commands:" << endl;
		cout << commandHandler->commands[1]->alias << ": List of commands." << endl;
		cout << commandHandler->commands[0]->alias << " [location to change to]: Change location." << endl;
		cout << commandHandler->commands[2]->alias << " [command alias] [alias to change to]: Change command's alias." << endl;
	}
};

class Alias : public Command {
public:
	Alias(string alias, CommandHandler* commandHandler) : Command(alias, commandHandler) {
	}

	void execute(vector<string> arg) override {
		for (Command* command : commandHandler->commands) {
			if (arg[1] == command->alias)
				command->ChangeAlias(arg[2]);
		}
		cout << alias << " command received. Command " << arg[1] << " changed to " << arg[2] << endl;
	}
};

int main() {
	CommandHandler handler;
	Go* goCmd = new Go("go", &handler);
	Help* helpCmd = new Help("help", &handler);
	Alias* aliasCmd = new Alias("change", &handler);

	string input;

	while (true)
	{
		std::getline(std::cin, input);

		handler.HandleCommand(input);
	}
	return 0;
}