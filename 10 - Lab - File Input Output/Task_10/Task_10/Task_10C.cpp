#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int main() {
	string line;

	ifstream readTest3("testFile3.json", ios::in);
	json j;
	readTest3 >> j;
	cout << j["jsonType"] << endl;
	cout << j["name"] << endl;
	cout << j["uuid"] << endl;
	cout << j["health"] << endl;
	cout << j["exp"] << endl;
	cout << j["level"] << endl;

	readTest3.close();

	return 0;
}