#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
using namespace std;

void SeparateAndPrin(string& line) {
	//Code learned from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	string delimiter = ":";

	size_t pos = 0;
	string token;
	while ((pos = line.find(delimiter)) != string::npos) {
		token = line.substr(0, pos);
		cout << token << endl;
		line.erase(0, pos + delimiter.length());
	}
	cout << line << endl;
}

int main() {
	string line;

	ifstream readTest3("testFile3.json", ios::in);
	while (!readTest3.eof()) {
		getline(readTest3, line);

		if (line.length() != 0 && line[0] != '#') {
			cout << line << endl;
		}
	}

	readTest3.close();

	return 0;
}