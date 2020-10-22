#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	//Code learned from http://www.cplusplus.com/doc/tutorial/files/
	string line;

	ifstream readTest2("testFile2.txt", ios::in | ios::binary);
	if (readTest2.is_open()) {
		while (getline(readTest2, line)) {
			cout << line << endl;
		}
		readTest2.close();
	}

	return 0;
}