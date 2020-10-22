#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void SeparateAndPrint(string& line) {
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
	//Code learned from http://www.cplusplus.com/doc/tutorial/files/ and http://www.cplusplus.com/forum/beginner/86013/
	string line;

	ifstream readTest2("testFile2.txt", ios::in);
	while (!readTest2.eof()) {
		getline(readTest2, line);
		
		if (line.length() != 0 && line[0] != '#') {
			SeparateAndPrint(line);
		}
	}

	readTest2.close();

	return 0;
}