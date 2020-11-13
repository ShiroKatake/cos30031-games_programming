#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Location {
public:
	string name;
	std::map<string, Location*> exits;
};

class Player {
public:
	Location* currentLocation;
};

int main() {
	Player* player = new Player();

	Location* A = new Location();
	Location* B = new Location();
	Location* C = new Location();

	A->exits.insert(make_pair("N", B));
	B->exits.insert(make_pair("U", C));
	C->exits.insert(make_pair("D", B));

	A->name = "A";
	B->name = "B";
	C->name = "C";

	player->currentLocation = A;

	string input;
	cout << "init finished" << endl;

	while (true) {
		cin >> input;
		player->currentLocation = player->currentLocation->exits[input];
		cout << "Location reached: " << player->currentLocation->name << endl;
	}

	return 0;
}