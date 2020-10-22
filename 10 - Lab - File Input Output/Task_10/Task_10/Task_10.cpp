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

	ofstream testFile1("testFile1.bin", ios::binary);
	testFile1.write(&myClass->myChar, sizeof(myClass->myChar));
	testFile1.write(reinterpret_cast<const char*>(&myClass->myInt), sizeof(myClass->myInt));
	testFile1.write(reinterpret_cast<const char*>(&myClass->myFloat), sizeof(myClass->myFloat));
	testFile1.close();
	
	return 0;
}