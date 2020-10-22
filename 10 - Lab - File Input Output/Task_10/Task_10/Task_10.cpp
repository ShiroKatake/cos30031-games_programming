#include <iostream>
#include <fstream>
using namespace std;

class MyClass {
public:
	MyClass(char charInput, int intInput, float floatInput) {
		myChar = charInput;
		myInt = intInput;
		myFloat = floatInput;
	}
public:
	char myChar;
	int myInt;
	float myFloat;
};

int main() {

	MyClass* myClass = new MyClass('asdf', 10, 3.2f);
/*
	ofstream writeTest1("testFile1.bin", ios::binary);
	writeTest1.write(&myClass->myChar, sizeof(myClass->myChar));
	writeTest1.write(reinterpret_cast<const char*>(&myClass->myInt), sizeof(myClass->myInt));
	writeTest1.write(reinterpret_cast<const char*>(&myClass->myFloat), sizeof(myClass->myFloat));
	writeTest1.close();*/
	
	char myCharRead = NULL;
	int myIntRead = NULL;
	float myFloatRead= NULL;

	ifstream readTest1("testFile1.bin", ios::in | ios::binary);
	readTest1.read(&myCharRead, sizeof(myClass->myChar));
	readTest1.read(reinterpret_cast<char *>(&myIntRead), sizeof(myClass->myInt));
	readTest1.read(reinterpret_cast<char *>(&myFloatRead), sizeof(myClass->myFloat));
	readTest1.close();

	cout << "char: " << myCharRead << endl;
	cout << "int: " << myIntRead << endl;
	cout << "float: " << myFloatRead << endl;

	return 0;
}