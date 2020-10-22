#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	//Code learned from http://www.cplusplus.com/doc/tutorial/files/
	string line;

	ifstream readTest2("testFile2.txt", ios::in);
	while (!readTest2.eof()) {
		getline(readTest2, line);
		
		if (line.length() != 0 && line[0] != '#') {
			cout << line << endl;
		}
	}
	readTest2.close();

	return 0;
}